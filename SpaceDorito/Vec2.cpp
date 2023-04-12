#pragma once
#include "Vec2.h"
#include <iostream>


Vec2::Vec2() {};
Vec2::Vec2(float xin, float yin)
	:x(xin), y(yin)
{
}
Vec2::Vec2(const Vec2& rhs)
	:x(rhs.x), y(rhs.y)
{
}


bool Vec2::operator == (const Vec2& rhs) const 
{ 
	return (x == rhs.x && y == rhs.y);
}
bool Vec2::operator != (const Vec2& rhs) const 
{
	return (x != rhs.x || y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}
Vec2 Vec2::operator / (const float rhs) const
{
	if (!rhs)
	{
		std::cout << "\nError. Divided by 0. Returning a default vec2.\n";
		return Vec2();
	}
	return Vec2(x / rhs, y / rhs);
}
Vec2 Vec2::operator * (const float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}
void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}
void Vec2::operator *= (const float rhs)
{
	x *= rhs;
	y *= rhs;
}
void Vec2::operator /= (const float rhs)
{
	if (!rhs)
	{
		std::cout << "\nError. Divided by 0. Returning a default vec2.\n";
		return;
	}
	x /= rhs;
	y /= rhs;
}

//Get distance between this vec2 and another vec2
float Vec2::distance(const Vec2& rhs) const
{
	return sqrt((rhs.x - x) * (rhs.x - x) + (rhs.y - y) * (rhs.y - y));
}
//Get magnitude
float Vec2::length() const
{
	return sqrt(x * x + y * y);
}
//Turn this Vec2 into a unit vector
Vec2 Vec2::normalize()
{
	float magnitude = length();
	*this /= magnitude;
	return *this;
}