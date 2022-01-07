#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include <vector>
#include "Managers.h"

#include "EngineRenderer.h"
#include "TextureBank.h"
#include "Entity.h"
#include "BallComponent.h"
#include "CollisionComponent.h"
#include "SpriteRenderer.h"

//-----------------------------------------------------------------------------
// Logic Info.
//-----------------------------------------------------------------------------

void Init();
void Update();
void Exit();

//Debug varibales
//double frameRateCurrentTimer = 0.;
//unsigned int numFrames = 0;

//char buffer[5];
//char buffer2[100];
//char buffer3[100];
//
//char bufferBalls[100];
//char buffer1Balls[100];

//double realTime = 0.;
//double logicRunTime = 0.;

class World
{
private:
	World() {};
	static World* instance;
	
	std::vector<Entity*> entities;

public:
	static World* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new World();
		}
		return instance;
	}

	//To assure Logic Manager is not copied or created using a copy
	World(World& other) = delete;
	void operator=(const World&) = delete;

	std::vector<Entity*>* GetWorldEntities() { return &entities; }

	//Entities created are created with new but there is currently no delete
	void AddEntity(Entity* _newEntity) 
	{
		if (_newEntity)
		{
			entities.push_back(_newEntity);
		}
	}
};

#define NUM_BALLS 16

int Main(void)
{
	Init();	
  
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		Update();
	}

	Exit();

	return 0;
}

void Init() 
{
	//Generate all the balls
	for (int i = 0; i < NUM_BALLS; ++i)
	{
		Entity* newEntity = new Entity();
		newEntity->AddComponent<BallComponent>(2, 20.f, 16.f); //Add ball component
		newEntity->AddComponent<Collider>(1, 16.f); //Add collider component

		//Load sprite
		const char* ballSpriteRoute = "data/tyrian_ball.png";
		GLuint* ballSprite = TextureBank::GetInstance()->GetTexture(ballSpriteRoute);
		newEntity->AddComponent<SpriteRenderer>(2,ballSprite, 16.f, RenderLayer::Default); //Add sprite renderer component

		World::GetInstance()->AddEntity(newEntity);
	}

	//LogicManager::GetInstance()->Init(NUM_BALLS);
	//EngineRenderer::GetInstance()->InitRenderEngine();
	FONT_Init();

	//Debug Prints
	//sprintf(buffer, "%d\n", numFrames);
	//sprintf(buffer2, "%.2f\n", realTime);
	//sprintf(buffer3, "%.2f\n", logicRunTime);
}


void Update()
{
	LogicManager::GetInstance()->Update();

	//Debug FPS
	//sprintf(buffer, "%.2f\n", 1./refreshTime);
	//FONT_DrawString(vec2(SCR_WIDTH / 2 - 20, SCR_HEIGHT - 25), buffer); //FPS print

	//Debug Logic vs Real Time
	//sprintf(buffer3, "LOGIC TIME: %.2f\n", logicRunTime);
	//realTime = realTime + time.GetRefreshTime();
	//sprintf(buffer2, "REAL TIME: %.2f\n", realTime);
	//FONT_DrawString(vec2(20, 140), buffer2); //Real time print
	//FONT_DrawString(vec2(20, 110), buffer3); //Logic time print

	
	//Debug Ball Speed with Delta vs Real Speed
	/*sprintf(bufferBalls, "REAL:%.2f, %.2f\n", 
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().x, 
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().y);*/
	/*sprintf(buffer1Balls, "SIMUL:%.2f, %.2f\n",
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().x * deltaTime,
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().y * deltaTime);*/
	//FONT_DrawString(vec2(20, 60), bufferBalls); //Real velocity
	//FONT_DrawString(vec2(20, 30), buffer1Balls); //Real velocity

	//GENERAL FUNCTIONS
	// Exchanges the front and back buffers
	SYS_Show();
	SYS_Pump();	// Process Windows messages.
}

void Exit()
{
	LogicManager::GetInstance()->Exit();
	FONT_End();
}