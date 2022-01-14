#pragma once
#include "Time.h"
#include <vector>

#define LOGIC_MANAGER_INSTANCE LogicManager::GetInstance()

class Entity;
class LogicManager 
{
public:
	enum class Size
	{
		Invalid = -1,
		Big,
		Medium,
		Small
	};

private:
	LogicManager() {};
	static LogicManager *instance;
public:
	static LogicManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new LogicManager();
		}
		return instance;
	}

	//To assure Logic Manager is not copied or created using a copy
	LogicManager(LogicManager& other) = delete;	
	void operator=(const LogicManager&) = delete;

	void Init();
	void Update();
	void Exit();

	void DivideBall(Entity* _ballToBreak, LogicManager::Size _sizeOfBall);
	void DestroyBall(Entity* _ballToDestroy);
};