#pragma once
#include <vector>

#define GAME_MANAGER_INSTANCE GameLogic::GetInstance()

class Entity;

class GameLogic
{
	//Variables
private:
	GameLogic() {}; //Private constructor to ensure it isn't called
	static GameLogic* instance; //Static Reference to self

	std::vector<Entity*> m_tEntities; //Entities that need to be updated
	std::vector<Entity*> m_tEnemies; //Reference to all enemies

	std::vector<Entity*> m_tEntitiesPreparedForDeletion; //Entities that will be destroy are put here
	
	const unsigned int NUM_SQUARES = 21; //Size of game field
	const int CHANCE_TO_SPAWN_ENEMY = 20; //Chance per frame to spawn an enemy

	Entity* m_pPlayer = nullptr; //Pointer to the player

	bool m_bKeepPlaying = true; //If true, the game will keep updating
	bool m_bEndingPlay = false; //If true, the game will reset after all entities have been updated

	unsigned int m_uPlayerKills; //Number of player kills
	unsigned int m_uPlayerDeaths; //Number of player deaths

	//Functions
public:
	//Singleton functions
	static GameLogic* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameLogic();
		}
		return instance;
	}

	//To assure GameLogic is not copied or created using a copy
	GameLogic(GameLogic& other) = delete;
	void operator=(const GameLogic&) = delete;


	void Init(); //Initializes game logic
	void Update(); //Updates all entities
	void Exit(); //Exits the game
	void StopPlay(); //Called when the player presses escape to stop playing
	void EndGame(); //Called when the player dies
	void ResetGame(); //Called to reset the map after a player's death

	void SpawnEnemy(int _randVal); //Spawns an enemy

	void ClearEntities(); //Deletes all entities that are in m_tEntitiesPreparedForDeletion

	void AddEntity(Entity* _newEntity) { m_tEntities.push_back(_newEntity); } //Adds an entity to the update list
	void RemoveEntity(Entity* _entityToRemove); //Removes an entity from the update list and deletes its memory from the heap
	
	void AddEnemy(Entity* _newEnemy) { m_tEnemies.push_back(_newEnemy); } //Adds an enemy to the reference list
	void RemoveEnemy(Entity* _entityToRemove); //Removes an entity from the reference list
	

	//Properties
	std::vector<Entity*>* const GetEntities() { return &m_tEntities; }
	std::vector<Entity*>* const GetEnemies() { return &m_tEnemies; }

	int GetPlayerPosition() const;

	unsigned int GetPlayerKills() { return m_uPlayerKills; }
	unsigned int GetPlayerDeaths() { return m_uPlayerDeaths; }

	const unsigned int GetSize() const { return NUM_SQUARES; }

	bool KeepPlaying() { return m_bKeepPlaying; }
};
