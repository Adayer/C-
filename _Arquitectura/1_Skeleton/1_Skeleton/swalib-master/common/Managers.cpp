#include "Managers.h"

LogicManager* LogicManager::instance = nullptr;

void LogicManager::Init(const unsigned int _numBalls)
{
	m_time.InitTime(); //Initialize time


	//Initialize balls
	m_balls.reserve(_numBalls);
	ballTexture = CORE_LoadPNG("data/tyrian_ball.png", false); //Load ball PNG
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

		//Move each of the balls
		for (size_t i = 0; i < numBalls; ++i)
		{
			m_balls[i]->Move(m_time.DeltaTime(), m_balls, i);
		}

		m_time.TickSlot(); //The needs to be called to update the time available for this task

		SYS_Sleep(17); //To prove it doesn't affect
	}
	
}

void LogicManager::Exit()
{	
	size_t numBalls = m_balls.size();
	
	for (int i = (numBalls - 1); i >= 0; --i)
	{
		m_balls[i]->Destroy(); //This method is called to assure a clean destruction of the balls
		delete m_balls[i]; //To avoid memory leaks (balls are created using "new")
		m_balls.pop_back();
	}

	//Unload ball PNG
	CORE_UnloadPNG(ballTexture);
}
