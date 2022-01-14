#include "Managers.h"
#include "World.h"
#include "Entity.h"
#include "BallComponent.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "InputManager.h"

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

}

void LogicManager::DestroyBall(Entity* _ballToDestroy)
{

}
