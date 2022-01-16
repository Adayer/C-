#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "sys.h"
#include "Component.h"
#include "Managers.h"


class BallComponent : public Component
{
private:
	vec2 m_currentVel; //Current Speed
	vec2 m_bufferPosition;
	float m_maxSpeed; //Max value for speed on any axis
	float m_radius;	//Radius of ball
	LogicManager::Size m_ballSize;
public:


	double GetRadius() { return m_radius; }
	vec2 GetVelocity() { return m_currentVel; }

	BallComponent(Entity* _root) :
		Component(_root),
		m_currentVel(0.f, 0.f),
		m_bufferPosition(0.f,0.f),
		m_maxSpeed(0.0f),
		m_radius(0.0f),
		m_ballSize(LogicManager::Size::Invalid)
	{

	};

	//4 args =  m_maxSpeed, m_radius, m_ballSize, vec2(initPos)
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	void Explode(); //Functionality for when ball is hit by bullet
	void InitExplodedBall(unsigned int _numArgs, ...); //Inits ball values if spawned by a ball exploding

	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;

	void OnEntityCollisionEnter(Entity* _otherEntity); //Called if collided with a ball
	void OnLimitCollisionEnter(bool _yAxis); //Called if collided with game border
};
