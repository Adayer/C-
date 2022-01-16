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
	const char* fullLifeSpriteRoute = "data/heart_full.png";
	GLuint* fullLifeSprite = TextureBank::GetInstance()->GetTexture(fullLifeSpriteRoute);
	const char* emptyLifeSpriteRoute = "data/heart_empty.png";
	GLuint* emptyLifeSprite = TextureBank::GetInstance()->GetTexture(emptyLifeSpriteRoute);

	//Generate Player
	Entity* newPlayer = EntityBank::GetInstance()->GetPlayerEntity();
	newPlayer->FindComponent<PlayerComponent>()->Init(5, vec2(SCR_WIDTH / 2, 38), 3, 200.f, fullLifeSprite, emptyLifeSprite);
	PlayerComponent* playerCmp = newPlayer->FindComponent<PlayerComponent>();
	newPlayer->FindComponent<Collider>()->Init(1, 20.f);
	newPlayer->FindComponent<GunComponent>()->Init(2, 15.f, 0.5f);

	const char* playerSpriteRoute = "data/player.png"; //Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* playerSprite = TextureBank::GetInstance()->GetTexture(playerSpriteRoute);
	newPlayer->FindComponent<SpriteRenderer>()->Init(3, playerSprite, vec2(40,40), RenderLayer::Default);
	
	AddEntity(newPlayer);

	for (unsigned int i = 0; i < 3; ++i)
	{
		Entity* newLife = new Entity();
		SpriteRenderer* cmpSprite = nullptr;
		newLife->AddComponent<SpriteRenderer>(cmpSprite ,3, fullLifeSprite, vec2(32, 32), RenderLayer::Foreground);
		playerCmp->AddLifeSpriteReference(cmpSprite);
		newLife->GetTransform()->SetPosition(vec2((SCR_WIDTH / 2) - 48  + 48 * i, SCR_HEIGHT - 50));
		AddEntity(newLife);
	}


	const char* ballSpriteRoute = "data/big_ball.png"; //Sprite route
	GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
	//Generate all the balls
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		//We add the components in a specific order so they update that way (Ball -> Collider -> Sprite)
		Entity* newEntity = EntityBank::GetInstance()->GetBallEntity();
		vec2 initBallPos(SCR_WIDTH / 2 - 82 * (NUM_BALLS / 2) + 82 * i,
			SCR_HEIGHT / 2 - 32 + (i % 2) * 32);
		newEntity->FindComponent<BallComponent>()->Init(4,70.f, BIG_BALL_DIAMETER, LogicManager::Size::Big, initBallPos); //Add ball component
		newEntity->FindComponent<Collider>()->Init(1, BIG_BALL_COL_RADIUS); //Add collider component
		newEntity->FindComponent<SpriteRenderer>()->Init(3, ballSprite, vec2(BIG_BALL_DIAMETER, BIG_BALL_DIAMETER), RenderLayer::Default); //Add sprite renderer component

		AddEntity(newEntity);
	}

	//Generate background -- NOT IN ENTITY BANK
	Entity* newBackground = new Entity();
	const char* backgroundSpriteRoute = "data/background.png";//Sprite route
	//We get the sprite from the TextureBank which will load it if it isn't already loaded
	GLuint* backgroundSprite = TextureBank::GetInstance()->GetTexture(backgroundSpriteRoute);
	newBackground->AddComponent<SpriteRenderer>(3, backgroundSprite, vec2(SCR_WIDTH, SCR_HEIGHT), RenderLayer::Background);
	newBackground->GetTransform()->SetPosition(vec2(SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f));
	AddEntity(newBackground);
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