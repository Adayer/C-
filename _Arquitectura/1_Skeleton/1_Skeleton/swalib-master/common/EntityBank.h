#pragma once
#include <vector>

#define ENTITY_BANK EntityBank::GetInstance()

class EntityBank
{

private:
	EntityBank() {};
	static EntityBank* instance;
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
	void Update();
	void Exit();
};