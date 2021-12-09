#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "Renderer.h"
#include <vector>
#include "Ball.h"
#include "Managers.h"



//-----------------------------------------------------------------------------
// Logic Info.
//-----------------------------------------------------------------------------

void Init();
void Update();
void Exit();
double GetTime();

//Variables necesarias para el calculo de tiempo entre frames
_int64 previousCount;
LARGE_INTEGER previousCountLarge;
LARGE_INTEGER currentCount;
LARGE_INTEGER frequency;

double fixedTick;
double previousTime = 0.f;
double refreshTime = 0.f;
double elapsedTime = 0.f;

double deltaTimeRatio = 1.; //Cambiar esto para alterar la velocidad de las pelotas
double deltaTime = 0.;

const float ELAPSED_TIME_MAX = 1.f / 15.f;


//Debug varibales
double frameRateCurrentTimer = 0.;
unsigned int numFrames = 0;

char buffer[5];
char buffer2[100];
char buffer3[100];

char bufferBalls[100];
char buffer1Balls[100];

double realTime = 0.;
double logicRunTime = 0.;

#define NUM_BALLS 16

int Main(void)
{
	Init();	
	fixedTick = 1. / 60.; //A mayor denumerador más veces se actualiza
	previousTime = GetTime();
  
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		Update();
	}

	Exit();

	return 0;
}



void Init() 
{
	LogicManager::GetInstance().InitBalls(NUM_BALLS);
	InitRenderer();
	
	FONT_Init();

	//Init Time values
	QueryPerformanceCounter(&previousCountLarge);
	previousCount = previousCountLarge.QuadPart;

	//Debug Prints
	sprintf(buffer, "%d\n", numFrames);
	sprintf(buffer2, "%.2f\n", realTime);
	sprintf(buffer3, "%.2f\n", logicRunTime);
}


void Update()
{
	refreshTime = GetTime();

	elapsedTime = elapsedTime + refreshTime;
	if (elapsedTime > ELAPSED_TIME_MAX)
	{
		elapsedTime = ELAPSED_TIME_MAX;
	}
	while(elapsedTime >= fixedTick)
	{
		deltaTime = elapsedTime / deltaTimeRatio;
		
		LogicManager::GetInstance().UpdateBalls(elapsedTime);

		elapsedTime = elapsedTime - fixedTick;
		logicRunTime += fixedTick;
		SYS_Sleep(17); 
	}
	UpdateRenderer();

	//Debug FPS
	sprintf(buffer, "%.2f\n", 1./refreshTime);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 20, SCR_HEIGHT - 25), buffer); //FPS print

	//Debug Logic vs Real Time
	sprintf(buffer3, "LOGIC TIME: %.2f\n", logicRunTime);
	realTime = realTime + refreshTime;
	sprintf(buffer2, "REAL TIME: %.2f\n", realTime);
	FONT_DrawString(vec2(20, 140), buffer2); //Real time print
	FONT_DrawString(vec2(20, 110), buffer3); //Logic time print

	
	//Debug Ball Speed with Delta vs Real Speed
	/*sprintf(bufferBalls, "REAL:%.2f, %.2f\n", 
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().x, 
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().y);*/
	/*sprintf(buffer1Balls, "SIMUL:%.2f, %.2f\n",
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().x * deltaTime,
		LogicManager::GetInstance()->GetBalls()[0].GetVelocity().y * deltaTime);*/
	FONT_DrawString(vec2(20, 60), bufferBalls); //Real velocity
	FONT_DrawString(vec2(20, 30), buffer1Balls); //Real velocity

	//GENERAL FUNCTIONS
	// Exchanges the front and back buffers
	SYS_Show();
	SYS_Pump();	// Process Windows messages.
}

void Exit()
{
	LogicManager::GetInstance().ExitBalls();
	ExitRenderer();
	FONT_End();
}


double  GetTime()
{
	QueryPerformanceCounter(&currentCount);
	QueryPerformanceFrequency(&frequency);
	_int64 resta = (currentCount.QuadPart - previousCount);

	double iResult = resta / static_cast<double>(frequency.QuadPart);
	previousCount = currentCount.QuadPart;

	 return iResult;
}