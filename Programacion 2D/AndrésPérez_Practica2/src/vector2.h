#pragma once
#include <cmath>

class vec2
{
public:
	float x; 
	float y; 

	vec2(float _x, float _y) :x(_x), y(_y)  {};
	vec2() :x(0.f), y(0.f)  {};
	vec2(const vec2& _other) { x = _other.x; y = _other.y; };


	vec2 operator+ (const vec2& _leftSide) const;	
	vec2 operator- (const vec2& _leftSide) const;
	vec2 operator* (const vec2& _leftSide) const;
	vec2 operator* (float _leftSide)const;
	vec2 operator/ (const vec2& _leftSide) const;
	vec2 operator/ (float _leftSide) const;
	vec2 operator= (const vec2& _vec) const;
	vec2 absolute(const vec2& _vec) const;
	float length() const;
	vec2 normalise(const vec2& _vec) const;
	vec2 normal(const vec2& _vec) const;
	float angle(const vec2& _vec) const;
};

float dot(const vec2& _a, const vec2& _b);
vec2 Normalize(const vec2& _vec);
vec2 Absolute(const vec2& _vec);
vec2 Normal(vec2 _vec);
float Angle(const vec2& _a, const vec2& _b);
float Distance(const vec2& _a, const vec2& _b);