#pragma once
#include "Time.h"
#include "Ball.h"
#include <vector>

#define LOGIC_MANAGER_INSTANCE LogicManager::GetInstance()
#define LOGIC_MANAGER_GET_BALLS LogicManager::GetInstance()->GetBalls()

class LogicManager 
{
private:
	std::vector<CBall*> m_balls; //Reference to all the balls controlled by the Logic Manager
	GLuint ballTexture = 0; //Texture to apply to each of the balls
	CTime m_time; //Time class for Logic Manager
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


	std::vector<CBall*>& GetBalls() { return m_balls; }
	CBall*& GetFirstBalls() { return m_balls[0]; }

	void Init(const unsigned int _numBalls);
	void Update();
	void Exit();
};