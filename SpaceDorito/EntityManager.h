#pragma once
#include "Entity.h"

//short hand
typedef std::vector <std::shared_ptr<Entity>> EntityVector; 
typedef std::map< std::string, EntityVector> EntityMap; 

class EntityManager
{
private: 
	EntityVector m_entities; 
	EntityMap m_entityMap;	
	size_t m_totalEntities = 0; 

	//delay adding entity into Vector to avoid iterator invalidation
	EntityVector m_toAdd; 

public: 
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	void destroy(Entity& e);
	EntityVector& getEntities();
	EntityVector& getEntities(const std::string& tag);


};