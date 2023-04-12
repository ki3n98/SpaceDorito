#include "EntityManager.h"


EntityManager::EntityManager() 
{
}

void EntityManager::update()
{
	//create entities
	for (auto& e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}
	m_toAdd.clear();

	//delete entities from vector
	for (int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->isAlive())
		{
			m_entities.erase(m_entities.begin() + i);
		}
	}
	//delete entities from map
	for (auto& e : m_entityMap)
	{
		for (int i = 0; i < e.second.size(); i++)
		{
			if (!e.second[i]->isAlive())
			{
				e.second.erase(e.second.begin() + i);
			}
		}
	}

	for (auto& e : m_entityMap["bullet"])
	{
		if (e->cLifeSpan->lifeSpan <= 0)
		{
			e->destroy();
		}
		e->cShape->circle.setFillColor(sf::Color(255, 0, 0, e->cLifeSpan->lifeSpan));
		e->cLifeSpan->lifeSpan -= 5;
	}

}

//create/add entity
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
	m_toAdd.push_back(e);
	return e;
}
void EntityManager::destroy(Entity& e)
{
	e.m_alive = false;
}

EntityVector& EntityManager::getEntities()
{
	return m_entities;
}
EntityVector& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap.at(tag);
}

