#include "World.h"
#include "EngineRenderer.h"
#include "TextureBank.h"
#include "Entity.h"
#include "BallComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"
#include "sys.h"

World* World::instance = nullptr;

void World::Init()
{
	//Generate Player
	Entity* newPlayer = new Entity();
	newPlayer->AddComponent<PlayerComponent>(2, vec2(SCR_HEIGHT/2, 40), 100.f);
	//Collider
	newPlayer->AddComponent<Collider>(1, 26.f);
	//Sprite
	const char* playerSpriteRoute = "data/mario.png"; //Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* playerSprite = TextureBank::GetInstance()->GetTexture(playerSpriteRoute);
	newPlayer->AddComponent<SpriteRenderer>(3, playerSprite, vec2(40, 40), RenderLayer::Default); //Add sprite renderer component
	
	//DEBUG PLAYER COLLISION
	//const char* debugSpriteRoute = "data/tyrian_ball.png"; //Sprite route
	//GLuint* debugSprite = TextureBank::GetInstance()->GetTexture(debugSpriteRoute);
	//newPlayer->AddComponent<SpriteRenderer>(3, debugSprite, vec2(36, 36), RenderLayer::Foreground); //Add sprite renderer component

	World::GetInstance()->AddEntity(newPlayer);

	//Generate all the balls
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		//We add the components in a specific order so they update that way (Ball -> Collider -> Sprite)
		Entity* newEntity = new Entity();
		newEntity->AddComponent<BallComponent>(2, 20.f, 16.f); //Add ball component
		newEntity->AddComponent<Collider>(1, 8.f); //Add collider component

		//Load sprite
		const char* ballSpriteRoute = "data/tyrian_ball.png"; //Sprite route
		//We get the sprite from the TextureBank which will load it if it isn't already loaded
		GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
		newEntity->AddComponent<SpriteRenderer>(3, ballSprite, vec2(16, 16), RenderLayer::Default); //Add sprite renderer component

		World::GetInstance()->AddEntity(newEntity);
	}

	//Generate background
	Entity* newBackground = new Entity();
	const char* backgroundSpriteRoute = "data/circle-bkg-128.png";//Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* backgroundSprite = TextureBank::GetInstance()->GetTexture(backgroundSpriteRoute);
	newBackground->AddComponent<TileableSpriteRenderer>(5, backgroundSprite, vec2(128,128), RenderLayer::Background, 128.f, 128.f);
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