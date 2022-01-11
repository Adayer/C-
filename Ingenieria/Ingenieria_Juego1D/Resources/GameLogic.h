#pragma once
#include <vector>

#define GAME_MANAGER_INSTANCE GameLogic::GetInstance()

class Entity;

class GameLogic
{
private:
	GameLogic() {};
	static GameLogic* instance;

	std::vector<Entity*> m_tEntities;
	
	const unsigned int NUM_SQUARES = 21;
	const int CHANCE_TO_SPAWN_ENEMY = 5;

	Entity* m_pPlayer = nullptr;

	bool bIsPlayerAlive = false;


public:
	static GameLogic* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameLogic();
		}
		return instance;
	}

	//To assure Logic Manager is not copied or created using a copy
	GameLogic(GameLogic& other) = delete;
	void operator=(const GameLogic&) = delete;


	void Init();
	void Update();
	void Exit();

	void SpawnEnemy(int _randVal);

	std::vector<Entity*>* GetEntities() { return &m_tEntities; }
	void AddEntity(Entity* _newEntity) { m_tEntities.push_back(_newEntity); }
	void RemoveEntity(Entity* _entityToRemove);

	const unsigned int GetSize() const { return NUM_SQUARES; }

	int GetPlayerPosition() const;
	void EndGame();

	bool IsPlayerAlive() { return bIsPlayerAlive; } //Para pruebas
};
