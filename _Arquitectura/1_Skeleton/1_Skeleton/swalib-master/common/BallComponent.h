#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "vector2d.h"
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "Component.h"


class BallComponent : public Component
{
private:
	vec2 m_currentVel; //Current Speed
	vec2 m_bufferPosition;
	float m_maxSpeed; //Max value for speed on any axis
	float m_radius = 16.f;	//Radius of ball
public:

	float GetRadius() { return m_radius; }
	vec2 GetVelocity() { return m_currentVel; }

	BallComponent(Entity* _root) :
		Component(_root),
		m_currentVel(0.f, 0.f),
		m_bufferPosition(0.f,0.f),
		m_maxSpeed(0.0f),
		m_radius(16.0f) 
	{

	};

	//2 args =  m_maxSpeed, m_radius
	virtual void Init(unsigned int _numArgs, va_list args) = 0;
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	void OnCollisionEnter();
};
