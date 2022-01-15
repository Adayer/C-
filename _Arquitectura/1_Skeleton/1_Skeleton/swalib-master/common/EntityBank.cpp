#include "BallComponent.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "Component.h"
#include "Entity.h"
#include "EntityBank.h"
#include "GunComponent.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"
#include "TextureBank.h"

EntityBank* EntityBank::instance = nullptr;

void EntityBank::Init()
{
	Entity* newPlayer = new Entity();
	newPlayer->AddComponent<PlayerComponent>(); //2, vec2(SCR_HEIGHT / 2, 40), 100.f
	newPlayer->AddComponent<GunComponent>();
	newPlayer->AddComponent<Collider>(); //1, 26.f
	newPlayer->AddComponent<SpriteRenderer>(); //Add sprite renderer component//3, playerSprite, vec2(40, 40), RenderLayer::Default

	m_playerEntity = newPlayer;

	for (unsigned int i = 0; i < BALL_POOL_SIZE; ++i)
	{
		Entity* newBall = new Entity();
		newBall->AddComponent<BallComponent>(); //Add ball component //3, 20.f, 16.f, LogicManager::Size::Small
		newBall->AddComponent<Collider>(); //Add collider component //1, 8.f
		newBall->AddComponent<SpriteRenderer>(); //Add sprite renderer component //3, ballSprite, vec2(16, 16), RenderLayer::Default

		m_tBallPool.push_back(newBall);
	}
	for(unsigned int i = 0; i < BULLET_POOL_SIZE; ++i)
	{
		Entity* newBullet = new Entity();

		newBullet->AddComponent<BulletComponent>(); //BulletComponent //2, 100.f, 8
		newBullet->AddComponent<Collider>(); //Collider //1,8.f
		newBullet->AddComponent<SpriteRenderer>();

		m_tBulletPool.push_back(newBullet);
	}
}


void EntityBank::Exit() //Deletes memory allocation of new entities initialized on world creation
{	
	int poolSize = m_tBallPool.size();
	for (int i = (poolSize - 1); i >= 0; --i)
	{
		delete m_tBallPool[i];
		m_tBallPool.pop_back();
	}

	poolSize = m_tBulletPool.size();
	for (int i = (poolSize - 1); i >= 0; --i)
	{
		delete m_tBulletPool[i];
		m_tBulletPool.pop_back();
	}
}

Entity* EntityBank::GetBallEntity()
{
	size_t poolSize = m_tBallPool.size();
	for (size_t i = 0; i < poolSize; ++i)
	{
		if (!m_tBallPool[i]->GetIsActive())
		{
			return m_tBallPool[i];
		}
	}
	return nullptr;
}
Entity* EntityBank::GetBulletEntity()
{
	size_t poolSize = m_tBulletPool.size();
	for (size_t i = 0; i < poolSize; ++i)
	{
		if (!m_tBulletPool[i]->GetIsActive())
		{
			return m_tBulletPool[i];
		}
	}
	return nullptr;
}