#pragma once
#include "vector2d.h"
#include "Component.h"
#include "InputManager.h"


class PlayerComponent : public Component
{
private:
	vec2 m_vPlayerInitPosition;
	float m_fPlayerSpeed;

public:
	PlayerComponent(Entity* _root) :
		Component(_root),
		m_vPlayerInitPosition(0, 0),
		m_fPlayerSpeed(0)
	{

	};

	//2 args =  m_maxSpeed, m_radius
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;

	void OnCollisionEnter();

	//Movement
	void MoveLeft();
	void MoveRight();
};
