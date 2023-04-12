#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include "EntityManager.h"
#include <SFML/Graphics.hpp>

const float PI = 3.141592f; 

class Game
{
private: 
	sf::RenderWindow	m_window; 
	EntityManager	    m_entities; 
	sf::Font			m_font; 
	sf::Text		    m_text; 
	sf::Event			m_event;
	int					m_score = 0; 
	int					m_currentFrame = 0; 
	int				    m_lastEnemySpawnTime = 0; 
	int					m_lastShootFrame = 0; 
	bool				m_pause = false;  
	bool				m_running = true; 

	
	std::shared_ptr<Entity> m_player; 
	
	void score();
	void start();
	void spawnPlayer();
	void playerMovement();
	void shoot();
	void spawnBullet(float speed, int radius);
	void enemySpawnRate(int framePerSpawn);
	void spawnEnemy();
	void transform();
	void establishBorder();
	void Collision();
	void restart();
	void handleInput();
	void destroyAll(const std::string tag);
	void pointAtMouse();
	void render();
	float tangent(float x, float y);
	float random(int min, int max);


public: 
	Game();
	void run();

};
