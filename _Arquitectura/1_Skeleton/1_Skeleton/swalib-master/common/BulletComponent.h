#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "sys.h"
#include "Component.h"
#include "Managers.h"


class BulletComponent : public Component
{
private:
	float m_speed; //Current bullet Y speed

public:
	BulletComponent(Entity* _root) :
		Component(_root),
		m_speed(0.f)
	{

	};

	//2 args =  m_speed, m_radius
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;

	void OnEntityCollisionEnter(Entity* _otherEntity); //Called if collided with Entity
	void OnLimitCollisionEnter(bool _yAxis); //Called if collided with Limit
};
