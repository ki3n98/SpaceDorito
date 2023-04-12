#include"Game.h"

Game::Game()
{
	start();
}
void Game::run()
{
	while (m_window.isOpen())
	{
		m_entities.update();
		enemySpawnRate(60);
		shoot();
		handleInput();
		pointAtMouse();
		playerMovement();
		establishBorder();
		transform();
		Collision();
		score();
		render();
		m_currentFrame++;
	}
}
void Game::score()
{

	m_text.setString("Score = " + std::to_string(m_score));
}

void Game::start()
{
	m_window.create(sf::VideoMode(800, 600), "SpaceDorito");
	m_window.setFramerateLimit(60);

	if (m_font.loadFromFile("fonts/ShareTech-Regular.ttf"))
	{
		std::cout << "ERROR";
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);


	spawnPlayer();
	spawnEnemy();
}

void Game::spawnPlayer()
{
	//Create player entity
	m_player = m_entities.addEntity("player");
	//Components
	m_player->cTransform = std::make_shared<CTransform>(Vec2(400.0f, 300.0f), Vec2(0.0, 0.0), 90);
	m_player->cShape = std::make_shared<CShape>(20.0f, 3, sf::Color(10, 10, 10), sf::Color::Red, 4.0f);
	m_player->cInput = std::make_shared<CInput>();
	m_player->cCollision = std::make_shared<CCollision>(20.0f);


}

void Game::playerMovement()
{
	//Player movement
	m_player->cTransform->velocity = { 0,0 };

	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 5;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5;
	}
}

void Game::shoot()
{
	if (m_player->cInput->shoot && m_currentFrame > (m_lastShootFrame + 20))
	{
		m_lastShootFrame = m_currentFrame;
		spawnBullet(20, 5);
	}
	m_player->cInput->shoot = false;

}

void Game::spawnBullet(float speed, int radius)
{
	auto e = m_entities.addEntity("bullet");
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

	float xDistance = mousePosition.x - m_player->cTransform->position.x;
	float yDistance = mousePosition.y - m_player->cTransform->position.y;

	Vec2 distanceVec(xDistance, yDistance);
	distanceVec.normalize();

	e->cTransform = std::make_shared<CTransform>(m_player->cTransform->position, distanceVec * speed, 0);
	e->cLifeSpan = std::make_shared<CLifeSpan>(255);
	e->cShape = std::make_shared<CShape>(radius, 12, sf::Color(255, 0, 0, e->cLifeSpan->lifeSpan), sf::Color::Black, 0);
	e->cCollision = std::make_shared<CCollision>(radius);
}
void Game::enemySpawnRate(int framePerSpawn)
{
	if (m_currentFrame == m_lastEnemySpawnTime)
	{
		spawnEnemy();
		m_lastEnemySpawnTime = m_currentFrame + framePerSpawn;
	}
	;
}
void Game::spawnEnemy()
{
	//Create enemy entity
	auto e = m_entities.addEntity("enemy");
	//Components
	float radius = random(10, 30);
	srand(time(0));
	e->cTransform = std::make_shared<CTransform>(Vec2(random(100, 700), random(100, 500)), Vec2(random(-5, 10), random(-5, 10)), 3);
	e->cShape = std::make_shared<CShape>(radius, random(4, 10), sf::Color(10, 10, 10), sf::Color::White, 3.0f);
	e->cCollision = std::make_shared<CCollision>(radius + 1);
	e->cScore = std::make_shared<CScore>(1);
}


float Game::random(int min, int max)
{
	float num = rand() % max + min;
	if (num == 0)
		return 1;

	return num;

}

void Game::transform()
{
	//Transform all entities
	for (auto& e : m_entities.getEntities())
	{
		e->cTransform->position += e->cTransform->velocity;
		e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);
	}

	//spin them
	for (auto& e : m_entities.getEntities("enemy"))
	{
		e->cShape->circle.setRotation(e->cShape->circle.getRotation() + e->cTransform->angle);
	}
}
void Game::establishBorder()
{
	float collisionRadius;
	//player collisions
	collisionRadius = m_player->cCollision->radius;
	if (m_player->cTransform->position.x >= m_window.getSize().x - collisionRadius)
	{
		m_player->cInput->right = false;
	}
	if (m_player->cTransform->position.x <= collisionRadius)
	{
		m_player->cInput->left = false;
	}

	if (m_player->cTransform->position.y >= m_window.getSize().y - collisionRadius)
	{
		m_player->cInput->down = false;
	}
	if (m_player->cTransform->position.y <= collisionRadius)
	{
		m_player->cInput->up = false;
	}

	//enemy collision on border
	for (auto& e : m_entities.getEntities("enemy"))
	{
		collisionRadius = e->cCollision->radius;
		if (e->cTransform->position.x >= m_window.getSize().x - collisionRadius || e->cTransform->position.x <= collisionRadius)
		{
			e->cTransform->velocity.x *= -1;
		}
		if (e->cTransform->position.y >= m_window.getSize().y - collisionRadius || e->cTransform->position.y <= collisionRadius)
		{
			e->cTransform->velocity.y *= -1;
		}
	}
}
void Game::Collision()
{
	for (auto& bullet : m_entities.getEntities("bullet"))
	{
		for (auto& enemy : m_entities.getEntities("enemy"))
		{
			if (bullet->cTransform->position.distance(enemy->cTransform->position) <= bullet->cCollision->radius + enemy->cCollision->radius)
			{
				m_score += enemy->cScore->score;
				bullet->destroy();
				enemy->destroy();

			}
		}
	}
	for (auto& enemy : m_entities.getEntities("enemy"))
	{
		if (m_player->cTransform->position.distance(enemy->cTransform->position) <= m_player->cCollision->radius + enemy->cCollision->radius)
		{
			restart();
		}
	}


}
void Game::restart()
{
	m_score = 0;
	destroyAll("enemy");
	m_player->cTransform->position = { 400,300 };
}

void Game::handleInput()
{
	while (m_window.pollEvent(m_event))
	{

		if (m_event.type == sf::Event::Closed)
			m_window.close();

		if (m_event.type == sf::Event::KeyPressed)
		{
			switch (m_event.key.code)
			{
				//Player movement input
			case sf::Keyboard::W: m_player->cInput->up = true; break;
			case sf::Keyboard::S: m_player->cInput->down = true; break;
			case sf::Keyboard::A: m_player->cInput->left = true; break;
			case sf::Keyboard::D: m_player->cInput->right = true; break;

				//Other keybinds go down here
			case sf::Keyboard::P: spawnEnemy(); break;
			case sf::Keyboard::O: destroyAll("enemy"); break;
			case sf::Keyboard::T:				break;

			}
		}

		if (m_event.type == sf::Event::KeyReleased)
		{
			//Player movement input
			switch (m_event.key.code)
			{
			case sf::Keyboard::W: m_player->cInput->up = false; break;
			case sf::Keyboard::S: m_player->cInput->down = false;  break;
			case sf::Keyboard::A: m_player->cInput->left = false; break;
			case sf::Keyboard::D:m_player->cInput->right = false; break;
			}
			//Other keybinds go down here
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_player->cInput->shoot = true;
		}



	}
}
void Game::destroyAll(const std::string tag)
{
	//return if nothing is in tag
	if (m_entities.getEntities(tag).empty())
		return;

	for (auto& e : m_entities.getEntities(tag))
	{
		e->destroy();
	}
}
void Game::pointAtMouse()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

	float xDistance = mousePosition.x - m_player->cTransform->position.x;
	float yDistance = mousePosition.y - m_player->cTransform->position.y;
	float angleAdjustment = 90.0f;

	m_player->cShape->circle.setRotation(tangent(xDistance, yDistance) + angleAdjustment);

}

float Game::tangent(float x, float y)
{
	return atan2(y, x) * (180.0f / PI);
}

void Game::render()
{
	m_window.clear();

	for (auto& e : m_entities.getEntities())
	{
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_text);
	m_window.display();
}