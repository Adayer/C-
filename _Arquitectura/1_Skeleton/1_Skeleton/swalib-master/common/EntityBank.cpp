#include "EntityBank.h"

#include "Entity.h"
#include "BallComponent.h"
#include "BulletComponent.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "SpriteRenderer.h"
#include "TextureBank.h"

EntityBank* EntityBank::instance = nullptr;

void EntityBank::Init()
{
	for (unsigned int i = 0; i < BALL_POOL_SIZE; ++i)
	{
		Entity* newBall = new Entity();
		newBall->AddComponent<BallComponent>(); //Add ball component //3, 20.f, 16.f, LogicManager::Size::Small
		newBall->AddComponent<Collider>(); //Add collider component //1, 8.f

		//Load sprite
		const char* ballSpriteRoute = "data/tyrian_ball.png"; //Sprite route
		//We get the sprite from the TextureBank which will load it if it isn't already loaded
		GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
		newBall->AddComponent<SpriteRenderer>(); //Add sprite renderer component //3, ballSprite, vec2(16, 16), RenderLayer::Default

		m_tBallPool.push_back(newBall);
	}
	for(unsigned int i = 0; i < BULLET_POOL_SIZE; ++i)
	{
		Entity* newBullet = new Entity();

		newBullet->AddComponent<BulletComponent>(); //BulletComponent //2, 100.f, 8
		newBullet->AddComponent<Collider>(); //Collider //1,8.f
	}
}


void EntityBank::Exit()
{	
}