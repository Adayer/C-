#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "vector2d.h"
#include "stdafx.h"
#include "core.h"
#include "sys.h"


class CBall
{
private:
	vec2   m_currentPos;	// Position.
	vec2   m_currentVel;	// Velocity.
	float   m_maxSpeed;	// Velocity.
	GLuint m_texture;	// OpenGL for id. for visualization purposes. 
	float  m_radius = 16.f;	// Radius.
public:

	float GetRadius() { return m_radius; }
	vec2 GetPosition() { return m_currentPos; }
	vec2 GetVelocity() { return m_currentVel; }

	CBall() :
		m_currentPos(0.0f),
		m_currentVel(0,0),
		m_maxSpeed(0.f),
		m_texture(0),
		m_radius(0.0f)
	{}
	void Create();
	void Move(double _deltaTime, std::vector<CBall> &_otherBalls, size_t _thisIndex);
	void Destroy();
};
