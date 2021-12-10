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
	vec2   m_currentPos;
	vec2   m_currentVel;
	float   m_maxSpeed;
	GLuint m_texture;
	float  m_radius = 16.f;	
public:

	float GetRadius() { return m_radius; }
	vec2 GetPosition() { return m_currentPos; }
	vec2 GetVelocity() { return m_currentVel; }
	GLuint GetTexture() { return m_texture; }

	CBall(GLuint _texture) :
		m_currentPos(0.0f),
		m_currentVel(0.f,0.f),
		m_maxSpeed(80.f),
		m_texture(_texture),
		m_radius(16.0f)
	{
		Create();
	}


	void Create();
	void Move(double _deltaTime, std::vector<CBall*> &_otherBalls, size_t _thisIndex);
	void Destroy();
};
