#pragma once
#include "Ball.h"
#include <vector>

class LogicManager 
{
private:
	//static LogicManager* singleton;
	std::vector<CBall> m_balls;
	LogicManager() {};
public:
	static LogicManager& GetInstance()
	{
		static LogicManager instance;
		return instance;
	}
	
	/*static LogicManager* GetInstanceMal()
	{
		if (singleton != nullptr)
		{
			singleton = new LogicManager();
		}
		return singleton;
	}*/

	LogicManager(LogicManager& other) = delete;	
	void operator=(const LogicManager&) = delete;


	std::vector<CBall>& GetBalls() { return m_balls; }
	CBall& GetFirstBalls() { return m_balls[0]; }

	void UpdateBalls(double elapsedTime);
};