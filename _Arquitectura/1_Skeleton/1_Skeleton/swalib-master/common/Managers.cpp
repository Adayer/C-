#include "Managers.h"

void LogicManager::UpdateBalls(double elapsedTime)
{
	size_t numBalls = m_balls.size();

	for (size_t i = 0; i < numBalls; ++i)
	{
		m_balls[i].Move(elapsedTime, m_balls, i);
	}
}
