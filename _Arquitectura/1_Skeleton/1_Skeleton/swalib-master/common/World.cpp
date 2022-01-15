#include "BallComponent.h"
#include "CollisionComponent.h"
#include "EngineRenderer.h"
#include "Entity.h"
#include "EntityBank.h"
#include "GunComponent.h"
#include "PlayerComponent.h"
#include "SpriteRenderer.h"
#include "sys.h"
#include "TextureBank.h"
#include "World.h"

World* World::instance = nullptr;

void World::Init()
{
	//Generate Player
	Entity* newPlayer = EntityBank::GetInstance()->GetPlayerEntity();
	newPlayer->FindComponent<PlayerComponent>()->Init(2, vec2(SCR_HEIGHT / 2, 40), 100.f);
	newPlayer->FindComponent<Collider>()->Init(1, 24.f);
	newPlayer->FindComponent<GunComponent>()->Init(2, 20.f, 2.f);

	const char* playerSpriteRoute = "data/mario.png"; //Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* playerSprite = TextureBank::GetInstance()->GetTexture(playerSpriteRoute);
	newPlayer->FindComponent<SpriteRenderer>()->Init(3, playerSprite, vec2(40,40), RenderLayer::Default);
	
	//DEBUG PLAYER COLLISION
	//const char* debugSpriteRoute = "data/tyrian_ball.png"; //Sprite route
	//GLuint* debugSprite = TextureBank::GetInstance()->GetTexture(debugSpriteRoute);
	//newPlayer->AddComponent<SpriteRenderer>(3, debugSprite, vec2(52, 52), RenderLayer::Foreground); //Add sprite renderer component

	World::GetInstance()->AddEntity(newPlayer);

	const char* ballSpriteRoute = "data/tyrian_ball.png"; //Sprite route
	GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
	//Generate all the balls
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		//We add the components in a specific order so they update that way (Ball -> Collider -> Sprite)
		Entity* newEntity = EntityBank::GetInstance()->GetBallEntity();
		newEntity->FindComponent<BallComponent>()->Init(3, 40.f, BIG_BALL_DIAMETER, LogicManager::Size::Big); //Add ball component
		newEntity->FindComponent<Collider>()->Init(1, BIG_BALL_COL_RADIUS); //Add collider component
		newEntity->FindComponent<SpriteRenderer>()->Init(3, ballSprite, vec2(BIG_BALL_DIAMETER, BIG_BALL_DIAMETER), RenderLayer::Default); //Add sprite renderer component

		World::GetInstance()->AddEntity(newEntity);
	}

	//Generate background -- NOT IN ENTITY BANK
	Entity* newBackground = new Entity();
	const char* backgroundSpriteRoute = "data/circle-bkg-128.png";//Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* backgroundSprite = TextureBank::GetInstance()->GetTexture(backgroundSpriteRoute);
	newBackground->AddComponent<TileableSpriteRenderer>(5, backgroundSprite, vec2(128,128), RenderLayer::Background, 128.f, 128.f);
	World::GetInstance()->AddEntity(newBackground);
	m_backgroundEntity = newBackground;
}

void World::Update()
{
	ClearEntities();
}


void World::AddEntity(Entity* _newEntity)
{
	if (_newEntity)
	{
		_newEntity->SetActive(true);
		entities.push_back(_newEntity);
	}
}

void World::RemoveEntity(Entity* _entityToRemove)
{
	_entityToRemove->SetActive(false);
	_entityToRemove->GetTransform()->SetPosition(vec2(10000, 10000));
}

void World::ClearEntities() //Counts numOfEntites to be removed
{
	std::vector<Entity*>::iterator iter;
	int numEntitiesToClear = 0;
	for (iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if (!(*iter)->GetIsActive())
		{
			++numEntitiesToClear;
		}
	}
	ClearEntityFromList(numEntitiesToClear);
}
void World::ClearEntityFromList(int _numEntsToClear) //Remove entity from list and calls the same function reducing counter by one
{
	if (_numEntsToClear == 0)
	{
		return;
	}
	std::vector<Entity*>::iterator iter;
	for (iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if (!(*iter)->GetIsActive())
		{
			(*iter)->Exit();
			entities.erase(iter);
			ClearEntityFromList(--_numEntsToClear);
			break;
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
			colliders.erase(iter);
			return;
		}
	}
}

void World::Exit()
{
	delete m_backgroundEntity;
}