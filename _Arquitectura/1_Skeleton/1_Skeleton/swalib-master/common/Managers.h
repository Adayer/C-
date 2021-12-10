#pragma once
#include "Time.h"
#include "Ball.h"
#include <vector>

class LogicManager 
{
private:
	std::vector<CBall*> m_balls;
	GLuint ballTexture = 0;
	CTime m_time;
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

	LogicManager(LogicManager& other) = delete;	
	void operator=(const LogicManager&) = delete;

	std::vector<CBall*>& GetBalls() { return m_balls; }
	CBall*& GetFirstBalls() { return m_balls[0]; }

	void Init(const unsigned int _numBalls);
	void Update();
	void Exit();
};