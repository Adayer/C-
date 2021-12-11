#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "vector2d.h"
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "EngineRenderer.h"


class CBall
{
private:
	vec2   m_currentPos; //Position
	vec2   m_currentVel; //Current Speed
	float   m_maxSpeed; //Max value for speed on any axis
	float  m_radius = 16.f;	//Radius of ball
	CSprite* m_sprite; //Ball sprite

public:

	float GetRadius() { return m_radius; }
	vec2 GetPosition() { return m_currentPos; }
	vec2 GetVelocity() { return m_currentVel; }

	CBall() :
		m_currentPos(0.0f),
		m_currentVel(0.f, 0.f),
		m_maxSpeed(0.0f),
		m_radius(16.0f),
		m_sprite(nullptr)
	{

	}

	CBall(GLuint _texture) :
		m_currentPos(0.0f),
		m_currentVel(0.f, 0.f),
		m_maxSpeed(80.f),
		m_radius(16.0f)
	{
		CreateBall();
		m_sprite = new CSprite(_texture, vec2(m_radius * 2.f, m_radius * 2.f), m_currentPos);
	}


	void CreateBall(); //Sets random values to position and speed on creation

	//Updates the ball's position
	void MoveBall(double _deltaTime, std::vector<CBall*> &_otherBalls, size_t _thisIndex);
	
	//Update the sprite values so that it renders correctly, and render the ball
	void UpdateBallRenderer(); 

	void DestroyBall(); //Prepares the ball to be destroyed by Logic Manager
};
