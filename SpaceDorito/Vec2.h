#pragma once


class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2(); 
	Vec2(float xin, float yin); 

	Vec2(const Vec2& rhs); 
	bool operator == (const Vec2& rhs) const; 
	bool operator != (const Vec2& rhs) const; 

	Vec2 operator + (const Vec2& rhs) const; 
	Vec2 operator - (const Vec2& rhs) const; 
	Vec2 operator / (const float rhs) const; 
	Vec2 operator * (const float rhs) const; 

	void operator += (const Vec2& rhs); 
	void operator -= (const Vec2& rhs); 
	void operator *= (const float rhs); 
	void operator /= (const float rhs); 

	float distance(const Vec2& rhs) const; 
	float length() const; 
	Vec2 normalize(); 
};