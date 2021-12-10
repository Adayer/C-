#include "Managers.h"

LogicManager* LogicManager::instance = nullptr;

void LogicManager::Init(const unsigned int _numBalls)
{
	m_time.InitTime();


	m_balls.reserve(_numBalls);
	ballTexture = CORE_LoadPNG("data/tyrian_ball.png", false);
	for (unsigned int i = 0; i < _numBalls; ++i)
	{
		CBall* newBall = new CBall(ballTexture);
		m_balls.push_back(newBall);
	}
}

void LogicManager::Update()
{
	m_time.UpdateTime();

	while (m_time.ProcessSlots())
	{
		size_t numBalls = m_balls.size();

		for (size_t i = 0; i < numBalls; ++i)
		{
			m_balls[i]->Move(m_time.DeltaTime(), m_balls, i);
		}

		SYS_Sleep(17);
	}
	
}

void LogicManager::Exit()
{	
	size_t numBalls = m_balls.size();
	
	for (int i = (numBalls - 1); i >= 0; --i)
	{
		m_balls[i]->Destroy();
		m_balls.pop_back();
	}

	CORE_UnloadPNG(ballTexture);
}
