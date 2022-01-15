#pragma once
#include "vector2d.h"
#include "stdafx.h"
#include "core.h"
#include "sys.h"
#include "Component.h"
#include "Managers.h"


class GunComponent : public Component
{
private:
	float m_yBulletOffset;
	float m_reloadTime;

	bool m_isReloading = false;
	float m_currentReloadTimer;
public:
	GunComponent(Entity* _root) :
		Component(_root),
		m_yBulletOffset(0.f),
		m_reloadTime(0.f),
		m_currentReloadTimer(0.f)
	{

	};

	//2 args =  m_speed, m_radius
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override;
	virtual void Exit() override; //No implementation
	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;
	
	void Shoot();
};
