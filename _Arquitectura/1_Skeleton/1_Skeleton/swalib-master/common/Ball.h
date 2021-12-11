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
	vec2   m_currentPos; //Position
	vec2   m_currentVel; //Current Speed
	float   m_maxSpeed; //Max value for speed on any axis
	GLuint m_texture; //Ball texture
	float  m_radius = 16.f;	//Radius of ball
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


	void Create(); //Sets random values to position and speed on creation

	//Updates the ball's position
	void Move(double _deltaTime, std::vector<CBall*> &_otherBalls, size_t _thisIndex);
	void Destroy(); //Prepares the ball to be destroyed by Logic Manager
};
