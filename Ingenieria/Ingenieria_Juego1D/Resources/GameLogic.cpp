#include "GameLogic.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

#include <time.h>
#include <random>

GameLogic* GameLogic::instance = nullptr;

void GameLogic::Init()
{

	srand(time(nullptr)); //Random seed generation

	Entity* playerEntity = new Player(11, 'X');
	m_pPlayer = playerEntity;
	m_tEntities.push_back(playerEntity);

	bIsPlayerAlive = true;
}
void GameLogic::Update() //Update all world Entities
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->Update();
	}

	int fRandVal = rand() % 100;
	if(fRandVal < CHANCE_TO_SPAWN_ENEMY)
	{
		SpawnEnemy(fRandVal);
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

void GameLogic::SpawnEnemy(int _randVal)
{
	if (_randVal % 2) //If number even then spawn on the left side and going right (true)
	{
		Entity* newEnemy = new Enemy(0, 'O', true);
		m_tEntities.push_back(newEnemy);
	}
	else //If number odd then spawn on the right side and going left (false)
	{
		Entity* newEnemy = new Enemy(NUM_SQUARES, 'O', false);
		m_tEntities.push_back(newEnemy);
	}
}

int GameLogic::GetPlayerPosition() const
{
	return m_pPlayer->GetCurrentPosition(); 
}

void GameLogic::EndGame()
{
	m_pPlayer->Exit();
	//Other end of game logic
	bIsPlayerAlive = false;
}