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

	std::vector<Entity*>* GetEntities() { return &m_tEntities; }
	void AddEntity(Entity* _newEntity) { m_tEntities.push_back(_newEntity); }
	void RemoveEntity(Entity* _entityToRemove);

	const unsigned int GetSize() const { return NUM_SQUARES; }
};
