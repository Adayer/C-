#pragma once
#include <vector>

#define ENTITY_BANK EntityBank::GetInstance()

class Entity;
class EntityBank
{
private:
	EntityBank() {};
	static EntityBank* instance;

	const unsigned int BALL_POOL_SIZE = 64;
	std::vector<Entity*> m_tBallPool;

	const unsigned int BULLET_POOL_SIZE = 16;
	std::vector<Entity*> m_tBulletPool;

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
};