#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include <vector>
#include "Managers.h"
#include "EngineRenderer.h"
#include "World.h"

//#include "EngineRenderer.h"
//#include "TextureBank.h"
//#include "Entity.h"
//#include "BallComponent.h"
//#include "CollisionComponent.h"
//#include "SpriteRenderer.h"

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

//#define NUM_BALLS 16

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
	World::GetInstance()->Init();
	LogicManager::GetInstance()->Init();
	EngineRenderer::GetInstance()->InitRenderEngine();
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
	EngineRenderer::GetInstance()->UpdateRenderer(); //We update the Engine separately to ensure it updates after the logic



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
	
}

void Exit()
{
	EngineRenderer::GetInstance()->ExitRenderer();
	LogicManager::GetInstance()->Exit();
	World::GetInstance()->Exit();
	FONT_End();
}