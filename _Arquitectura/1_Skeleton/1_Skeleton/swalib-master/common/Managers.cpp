#include "Managers.h"
#include "World.h"
#include "Entity.h"
#include "BallComponent.h"
#include "Component.h"

LogicManager* LogicManager::instance = nullptr;

void LogicManager::Init()
{
	TIME->InitTime(); //Initialize time
}

void LogicManager::Update()
{
	TIME->UpdateTime();

	while (TIME->ProcessSlots())
	{
		//Move each of the balls
		std::vector<Entity*>* tEntities= World::GetInstance()->GetWorldEntities();
		size_t numEntities = tEntities->size();
		for (size_t i = 0; i < numEntities; ++i)
		{
			BallComponent* pBall = (*tEntities)[i]->FindComponent<BallComponent>();
			if (pBall)
			{
				pBall->Update();
			}
		}
		
		TIME->TickSlot(); //The needs to be called to update the time available for this task
	}
}

void LogicManager::Exit()
{	
	//PENDING?
}
