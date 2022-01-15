#include "GunComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"
#include "InputManager.h"
#include "EntityBank.h"
#include "World.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "SpriteRenderer.h"
#include "TextureBank.h"

void GunComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 2)
	{
		m_yBulletOffset = va_arg(args, double);
		m_reloadTime = va_arg(args, double);
	}
	m_isReloading = false;
	m_currentReloadTimer = 0;

	InputManager::GetInstance()->RegisterOnSpacePressed(std::bind(&GunComponent::Shoot, this));
}
void GunComponent::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}

void GunComponent::Update()
{
	if (m_isReloading)
	{
		m_currentReloadTimer -= TIME_DELTA_TIME;
		if (m_currentReloadTimer <= 0.f)
		{
			m_isReloading = false;
			m_currentReloadTimer = 0.f;
		}
	}
}

void GunComponent::Exit()
{

}

void GunComponent::RecieveMessage(Message* _message, Message::MessageType _typeOfMessage)
{

}

void GunComponent::Shoot()
{
	if (m_isReloading)
	{
		return;
	}

	Entity* newBullet = EntityBank::GetInstance()->GetBulletEntity();
	if (!newBullet)
	{
		return;
	}
	newBullet->GetTransform()->SetPosition(vec2(root->GetTransform()->GetPosition().x, root->GetTransform()->GetPosition().y + m_yBulletOffset));
	newBullet->SetActive(true);

	newBullet->FindComponent<BulletComponent>()->Init(1,100.f);
	newBullet->FindComponent<Collider>()->Init(7.f);

	const char* bulletSpriteRoute = "data/tyrian_ball.png"; //Sprite route
	GLuint* bulletSprite = TextureBank::GetInstance()->GetTexture(bulletSpriteRoute);
	newBullet->FindComponent<SpriteRenderer>()->Init(3, bulletSprite, vec2(10,10), RenderLayer::Foreground);

	World::GetInstance()->AddEntity(newBullet);

	m_currentReloadTimer = m_reloadTime;
	m_isReloading = true;
}