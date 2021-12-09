#include "Managers.h"

void LogicManager::InitBalls(const unsigned int _numBalls)
{
	m_balls.reserve(_numBalls);
	for (unsigned int i = 0; i < _numBalls; ++i)
	{
		m_balls.push_back(CBall());
	}
}

void LogicManager::UpdateBalls(double elapsedTime)
{
	size_t numBalls = m_balls.size();

	for (size_t i = 0; i < numBalls; ++i)
	{
		m_balls[i].Move(elapsedTime, m_balls, i);
	}
}

void LogicManager::ExitBalls()
{	
	size_t numBalls = m_balls.size();
	
	for (unsigned int i = numBalls; i > 0; --i)
	{
		m_balls[i].Destroy();
		m_balls.pop_back();
	}
}
