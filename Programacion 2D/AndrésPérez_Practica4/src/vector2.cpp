#include "vector2.h"

vec2 vec2::operator+ (const vec2& _leftSide) const
{
	return vec2(x + _leftSide.x, y + _leftSide.y);
}

vec2 vec2::operator- (const vec2& _leftSide) const
{
	return vec2(x - _leftSide.x, y - _leftSide.y);
}

vec2 vec2::operator* (const vec2& _leftSide) const
{
	return vec2(x * _leftSide.x, y * _leftSide.y);
}
vec2 vec2::operator* (float _leftSide)const
{
	return vec2(x * _leftSide, y * _leftSide);
}
vec2 vec2::operator/ (const vec2& _leftSide) const
{
	return vec2(x / _leftSide.x, y / _leftSide.y);
}


vec2 vec2::operator/ (float _leftSide) const
{
	return vec2(x / _leftSide, y / _leftSide);
}
vec2 vec2::operator= (const vec2& _vec) const
{
	return vec2(_vec.x, _vec.y);
}

vec2 vec2::absolute(const vec2& _vec) const
{
	return vec2(abs(_vec.x), abs(_vec.y));
}
float vec2::length() const
{
	return sqrt(x * x + y * y);
}
vec2 vec2::normalise(const vec2& _vec) const
{
	float length(length());
	vec2 result(_vec.x / length, _vec.y / length);
	return result;
}
vec2 vec2::normal(const vec2& _vec) const
{
	return vec2(_vec.y, -_vec.x);
}
float vec2::angle(const vec2& _vec) const
{
	vec2 vector(x - _vec.x, y - _vec.y);
	return vector.length();
}

//Genericas
float dot(const vec2& _a, const vec2& _b)
{
	return (_a.x * _b.x + _a.y * _b.y);
}

vec2 Normalize(const vec2& _vec)
{
	float length(_vec.length());
	vec2 result(_vec.x / length, _vec.y / length);
	return result;
}
vec2 Absolute(const vec2& _vec)
{
	return _vec.absolute(_vec);
}

vec2 Normal(vec2 _vec)
{
	return _vec.normal(_vec);
}

float Angle(const vec2& _a, const vec2& _b)
{
	return (atan2f(_a.y * _b.x - _a.x * _b.y, _a.x * _b.x + _a.y * _b.y));
}
float Distance(const vec2& _a, const vec2& _b)
{
	vec2 vector(_a - _b);
	return vector.length();
}