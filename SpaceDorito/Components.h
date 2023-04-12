#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

// C infront of every class stand for Component

class CTransform
{
public: 
	Vec2 position = { 0.0,0.0 }; 
	Vec2 velocity = { 0.0, 0.0 }; 
	float angle = 0; 

	CTransform(const Vec2& posIn, const Vec2& velIn, float angleIn)
		:position(posIn), velocity(velIn), angle(angleIn)
	{
	}
};

class CShape
{
public: 
	sf::CircleShape circle; 

	CShape(float radius, int points, const sf::Color& fill, 
		const sf::Color& outlineColor, float thickness)
		:circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outlineColor);
		circle.setOutlineThickness(thickness); 
		circle.setOrigin(radius, radius); 
	}
};

class CCollision
{
public:
	float radius = 0; 

	CCollision(float r)
		:radius(r)
	{
	}
};

class CScore
{
public: 
	int score = 0;

	CScore(int s)
		:score(s)
	{
	}
};

class CLifeSpan
{
public:
	int lifeSpan = 0; 

	CLifeSpan(int lifeSpanIn)
		:lifeSpan(lifeSpanIn)
	{
	}
};

class CInput
{
public: 
	bool up = false; 
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput()
	{
	}
};