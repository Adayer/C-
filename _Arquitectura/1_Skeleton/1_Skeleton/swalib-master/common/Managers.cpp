#include "Managers.h"

LogicManager* LogicManager::instance = nullptr;

void LogicManager::Init(const unsigned int _numBalls)
{
	m_time.InitTime(); //Initialize time

	backgroundTexture = CORE_LoadPNG("data/circle-bkg-128.png", true);
	m_backgroundSprite = new CTileableSprite(backgroundTexture, vec2(128, 128), vec2(0.f, 0.f), 128, 128);
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

	size_t numBalls = m_balls.size();
	while (m_time.ProcessSlots())
	{

		//Move each of the balls
		for (size_t i = 0; i < numBalls; ++i)
		{
			m_balls[i]->MoveBall(m_time.DeltaTime(), m_balls, i);
		}
		
		m_time.TickSlot(); //The needs to be called to update the time available for this task

		//SYS_Sleep(17); //Uncomment to prove it doesn't affect
	}

	//Update Sprites
	m_backgroundSprite->UpdateSpriteRender();

	for (size_t i = 0; i < numBalls; ++i)
	{
		m_balls[i]->UpdateBallRenderer();
	}
}

void LogicManager::Exit()
{	
	size_t numBalls = m_balls.size();
	
	for (int i = (numBalls - 1); i >= 0; --i)
	{
		m_balls[i]->DestroyBall(); //This method is called to assure a clean destruction of the balls
		delete m_balls[i]; //To avoid memory leaks (balls are created using "new")
		m_balls.pop_back();
	}

	//Delete background pointer
	delete m_backgroundSprite;
	m_backgroundSprite = nullptr;
	
	//Unload PNGs
	CORE_UnloadPNG(ballTexture);
	CORE_UnloadPNG(backgroundTexture);
}
