#include "World.h"
#include "EngineRenderer.h"
#include "TextureBank.h"
#include "Entity.h"
#include "BallComponent.h"
#include "CollisionComponent.h"
#include "SpriteRenderer.h"

World* World::instance = nullptr;

void World::Init()
{
	//Generate all the balls
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		Entity* newEntity = new Entity();
		newEntity->AddComponent<BallComponent>(2, 20.f, 16.f); //Add ball component
		newEntity->AddComponent<Collider>(1, 16.f); //Add collider component

		//Load sprite
		const char* ballSpriteRoute = "data/tyrian_ball.png";
		GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
		newEntity->AddComponent<SpriteRenderer>(2, ballSprite, 16.f, RenderLayer::Default); //Add sprite renderer component

		World::GetInstance()->AddEntity(newEntity);
	}

	//Generate background
	Entity* newBackground = new Entity();
	const char* backgroundSpriteRoute = "data/circle-bkg-128.png";
	newBackground->AddComponent<TileableSpriteRenderer>(5, backgroundSpriteRoute, 128, RenderLayer::Background, 128, 128);
	World::GetInstance()->AddEntity(newBackground);
}

void World::RemoveEntity(Entity* _entityToRemove)
{

	std::vector<Entity*>::iterator iter;

	for (iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if (*iter == _entityToRemove)
		{
			_entityToRemove->Exit();
			Entity** pToPointerToDelete = &*iter;
			entities.erase(iter);
			delete *pToPointerToDelete;
		}
	}
}

void World::RemoveCollider(Collider* _colliderToRemove)
{

	std::vector<Collider*>::iterator iter;

	for (iter = colliders.begin(); iter != colliders.end(); ++iter)
	{
		if (*iter == _colliderToRemove)
		{
			colliders
				.erase(iter);
		}
	}
}

void World::Exit()
{

}