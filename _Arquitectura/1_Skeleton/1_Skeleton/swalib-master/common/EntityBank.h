#pragma once
#include <vector>

#define ENTITY_BANK EntityBank::GetInstance()

class Entity;

//This class creates Entities with preconfigured component structures but no values initialized
//This class is also in charge of those entity's deletion
class EntityBank
{
private:
	EntityBank() {};
	static EntityBank* instance;

	const unsigned int BALL_POOL_SIZE = 64;
	std::vector<Entity*> m_tBallPool;

	const unsigned int BULLET_POOL_SIZE = 16;
	std::vector<Entity*> m_tBulletPool;

	Entity* m_playerEntity;

public:
	static EntityBank* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new EntityBank();
		}
		return instance;
	}
	
	~EntityBank(){}

	//To assure Logic Manager is not copied or created using a copy
	EntityBank(EntityBank& other) = delete;
	void operator=(const EntityBank&) = delete;

	void Init();
	void Exit();

	Entity* GetBallEntity();
	Entity* GetBulletEntity();
	Entity* GetPlayerEntity() { return m_playerEntity; }
};