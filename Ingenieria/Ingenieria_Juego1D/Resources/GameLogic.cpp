#include "GameLogic.h"
#include "Entity.h"

GameLogic* GameLogic::instance = nullptr;

void GameLogic::Init()
{
	
}
void GameLogic::Update() //Update all world Entities
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->Update();
	}
}
void GameLogic::Exit()
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->Exit();
	}
}

void GameLogic::RemoveEntity(Entity* _entityToRemove)
{

	std::vector<Entity*>::iterator iter;

	for (iter = m_tEntities.begin(); iter != m_tEntities.end(); ++iter)
	{
		if (*iter == _entityToRemove)
		{
			_entityToRemove->Exit();
			Entity** pToPointerToDelete = &*iter;
			m_tEntities.erase(iter);
			delete* pToPointerToDelete;
			return;
		}
	}
}