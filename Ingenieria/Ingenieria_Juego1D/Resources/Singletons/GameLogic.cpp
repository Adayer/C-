#include "GameLogic.h"
#include "Renderer.h"

#include "../Entities/Enemy.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"

#include <time.h>
#include <random>
#include <Windows.h>
#include <Mmsystem.h>

GameLogic* GameLogic::instance = nullptr;

void GameLogic::Init()
{
	PlaySound(TEXT("Data/musica.wav"), NULL, SND_ASYNC | SND_LOOP); //Music loop starts

	srand(time(nullptr)); //Random seed generation

	//Player generation
	Entity* playerEntity = new Player(NUM_SQUARES / 2 + 1, 'O'); 
	m_pPlayer = playerEntity;
	m_tEntities.push_back(playerEntity);

	m_bKeepPlaying = true;
	m_bEndingPlay = false;
}
void GameLogic::Update() //Update all world Entities
{
	//Update all entities
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->Update();
	}

	//Spawn an enemy
	int fRandVal = rand() % 100;
	if(fRandVal < CHANCE_TO_SPAWN_ENEMY)
	{
		SpawnEnemy(fRandVal);
	}


	//If play continues: Delete entities prepared for deletion
	if (!m_bEndingPlay)
	{
		ClearEntities(); 
	}
	//Else: Reset the game 
	else
	{
		ResetGame();
	}

}
void GameLogic::Exit()
{
	size_t numEntities = m_tEntities.size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		m_tEntities[i]->Exit(); //Prepares the entities for deletion
	}

	//Deletes player memory
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void GameLogic::RemoveEntity(Entity* _entityToRemove) 
{
	//Entity is added to the list of deletion an set to not update
	m_tEntitiesPreparedForDeletion.push_back(_entityToRemove); 
	_entityToRemove->m_isActive = false;
}

void GameLogic::ClearEntities() 
{ 
	int numToDelete = m_tEntitiesPreparedForDeletion.size();
	for (int i = (numToDelete - 1); i >= 0; --i)
	{
		size_t numEntities = m_tEntities.size();
		for (size_t j = 0; j < numEntities; ++j)
		{
			if (m_tEntitiesPreparedForDeletion[i] == m_tEntities[j])
			{
				delete m_tEntitiesPreparedForDeletion[i];
				m_tEntities.erase(m_tEntities.begin() + j);
				m_tEntitiesPreparedForDeletion.pop_back();
				break;
			}
		}
	}
}

void GameLogic::RemoveEnemy(Entity* _enemyToRemove) //CAN'T DELETE ENTITY FROM HEAP
{
	size_t numEnemies = m_tEnemies.size();

	for (size_t i = 0; i < numEnemies; ++i)
	{
		if (m_tEnemies[i] == _enemyToRemove)
		{
			m_tEnemies.erase(m_tEnemies.begin() + i);
			RemoveEntity(_enemyToRemove);
			m_uPlayerKills++;
			return;
		}
	}
}

void GameLogic::SpawnEnemy(int _randVal)
{
	if (_randVal % 2) //If number even then spawn on the left side and going right (true)
	{
		Entity* newEnemy = new Enemy(0, '*', true);
		m_tEntities.push_back(newEnemy);
		m_tEnemies.push_back(newEnemy);
	}
	else //If number odd then spawn on the right side and going left (false)
	{
		Entity* newEnemy = new Enemy(NUM_SQUARES, '*', false);
		m_tEntities.push_back(newEnemy);
		m_tEnemies.push_back(newEnemy);
	}
}

int GameLogic::GetPlayerPosition() const
{
	return m_pPlayer->GetCurrentPosition(); 
}

//Tells the game to reset after Update
void GameLogic::EndGame()
{
	m_pPlayer->Exit();
	++m_uPlayerDeaths;
	m_bEndingPlay = true;
}

void GameLogic::StopPlay()
{
	m_bKeepPlaying = false;
}

void GameLogic::ResetGame() //Eliminates all entities and initializes the game logic , but keeps the score and renderer
{
	size_t numEnemies = m_tEnemies.size();
	for (size_t i = 0; i < numEnemies; ++i)
	{
		m_tEnemies.pop_back();
	}
	
	size_t numToDelete = m_tEntitiesPreparedForDeletion.size();
	for (size_t i = 0; i < numToDelete; ++i)
	{
		m_tEntitiesPreparedForDeletion.pop_back();
	}

	int numEntities = m_tEntities.size();
	for (int i = (numEntities - 1); i >= 0; --i)
	{
		delete m_tEntities[i];
		m_tEntities.pop_back();
	}

	Init();
}