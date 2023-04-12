#pragma once
#include "Components.h"



class Entity
{
private: 
	friend class EntityManager; 

	bool m_alive = true; 
	size_t m_id = 0; 
	std::string m_tag = "default"; 



public:
	//Make constructor Private so ONLY EntityManager can call constructor.
	Entity(const std::string& tag, const size_t id)
		:m_tag(tag), m_id(id)
	{
	}
	//component
	std::shared_ptr<CTransform> cTransform; 
	std::shared_ptr<CShape>		cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput>		cInput;
	std::shared_ptr<CScore>		cScore;
	std::shared_ptr<CLifeSpan>  cLifeSpan;


	//accessors 
	bool isAlive() const
	{
		return m_alive;
	}

	const std::string& tag() const
	{
		return m_tag; 
	}
	const size_t id() const
	{
		return m_id; 
	}
	void destroy()
	{
		m_alive = false; 
	}

};
