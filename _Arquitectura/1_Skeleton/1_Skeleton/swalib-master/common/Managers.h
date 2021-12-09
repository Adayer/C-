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

	LogicManager(LogicManager& other) = delete;	
	void operator=(const LogicManager&) = delete;

	std::vector<CBall>& GetBalls() { return m_balls; }
	CBall& GetFirstBalls() { return m_balls[0]; }

	void InitBalls(const unsigned int _numBalls);
	void UpdateBalls(double elapsedTime);
	void ExitBalls();
};