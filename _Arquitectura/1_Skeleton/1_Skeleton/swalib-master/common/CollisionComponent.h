#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "vector2d.h"
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "Component.h"



class Collider : public Component
{
private:
	float m_radius = 0.f;
public:

	Collider(Entity* _root) :
		Component(_root),
		m_radius(0.f)
	{

	}

	float GetRadius() { return m_radius; }
	void SetRadius(float _radius) 
	{ 
		if (_radius > 0)
		{
			_radius = 0.;
		}
		m_radius = _radius; 
	}

	//NumArgs 1 = m_radius;
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() {}
	virtual void Update() override;
	virtual void Exit() override; //No implementation

	virtual void RecieveMessage(Message* _message, Message::MessageType _messageType) override{}
};
