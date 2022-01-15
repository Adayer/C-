#include "Managers.h"
#include "World.h"
#include "Entity.h"
#include "BallComponent.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "InputManager.h"
#include "EntityBank.h"
#include "SpriteRenderer.h"
#include "TextureBank.h"

LogicManager* LogicManager::instance = nullptr;
#define COMPONENT_LIST (*((*tEntities)[i]->GetComponentList()))

void LogicManager::Init()
{
	TIME->InitTime(); //Initialize time
}

void LogicManager::Update()
{
	TIME->UpdateTime();

	while (TIME->ProcessSlots())
	{
		InputManager::GetInstance()->Update();
		//We update all components
		std::vector<Entity*>* tEntities= World::GetInstance()->GetWorldEntities();
		size_t numEntities = tEntities->size();
		for (size_t i = 0; i < numEntities; ++i)
		{
			size_t numComponents = (*tEntities)[i]->GetComponentList()->size();
			for (size_t j = 0; j < numComponents; ++j)
			{
				COMPONENT_LIST[j]->Update();
			}
		}
		
		TIME->TickSlot(); //The needs to be called to update the time available for this task
	}
}

void LogicManager::Exit()
{	
	//PENDING?
}

void LogicManager::DivideBall(Entity* _ballToBreak, LogicManager::Size _sizeOfBall)
{


	switch (_sizeOfBall)
	{
		case LogicManager::Size::Big:
		{
			const char* ballSpriteRoute = "data/tyrian_ball.png"; //Sprite route
			GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
			for (int i = 0; i < 2; ++i)
			{
				Entity* newBall = EntityBank::GetInstance()->GetBallEntity();
				if (newBall)
				{
					newBall->FindComponent<BallComponent>()->InitExplodedBall(4,40.f,BIG_BALL_DIAMETER / 2, LogicManager::Size::Medium, i);
					newBall->FindComponent<Collider>()->Init(1, BIG_BALL_COL_RADIUS / 2);
					newBall->FindComponent<SpriteRenderer>()->Init(3, ballSprite, vec2(BIG_BALL_DIAMETER/2, BIG_BALL_DIAMETER/2), RenderLayer::Default);

					newBall->SetActive(true);
					World::GetInstance()->AddEntity(newBall);

					if (i == 0)
					{
						vec2 ballToBreakPos = _ballToBreak->GetTransform()->GetPosition();
						newBall->GetTransform()->SetPosition(vec2(ballToBreakPos.x + BIG_BALL_DIAMETER / 4.f, ballToBreakPos.y));
					}
					else
					{
						vec2 ballToBreakPos = _ballToBreak->GetTransform()->GetPosition();
						newBall->GetTransform()->SetPosition(vec2(ballToBreakPos.x - BIG_BALL_DIAMETER / 4.f, ballToBreakPos.y));
					}
				}
			}
			break;
		}
		case LogicManager::Size::Medium:
		{
			const char* ballSpriteRoute = "data/tyrian_ball.png"; //Sprite route
			GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
			for (int i = 0; i < 2; ++i)
			{
				Entity* newBall = EntityBank::GetInstance()->GetBallEntity();
				if (newBall)
				{
					newBall->FindComponent<BallComponent>()->InitExplodedBall(4, 40.f, BIG_BALL_DIAMETER / 4.f, LogicManager::Size::Small,i);
					newBall->FindComponent<Collider>()->Init(1, BIG_BALL_COL_RADIUS / 4.f);
					newBall->FindComponent<SpriteRenderer>()->Init(3, ballSprite, vec2(BIG_BALL_DIAMETER / 4.f, BIG_BALL_DIAMETER / 4.f), RenderLayer::Default);

					newBall->SetActive(true);
					World::GetInstance()->AddEntity(newBall);
					if (i == 0)
					{
						vec2 ballToBreakPos = _ballToBreak->GetTransform()->GetPosition();
						newBall->GetTransform()->SetPosition(vec2(ballToBreakPos.x + BIG_BALL_DIAMETER / 8.f, ballToBreakPos.y));
					}
					else 
					{
						vec2 ballToBreakPos = _ballToBreak->GetTransform()->GetPosition();
						newBall->GetTransform()->SetPosition(vec2(ballToBreakPos.x - BIG_BALL_DIAMETER / 8.f, ballToBreakPos.y));
					}
				}
			}
			break;
		}
	}

	World::GetInstance()->RemoveEntity(_ballToBreak);
}

void LogicManager::DestroyBall(Entity* _ballToDestroy)
{
	World::GetInstance()->RemoveEntity(_ballToDestroy);
}
