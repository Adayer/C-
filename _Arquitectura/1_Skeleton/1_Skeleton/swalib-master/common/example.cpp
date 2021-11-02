#pragma once

#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "BallLogic.h"
#include "Renderer.h"


//-----------------------------------------------------------------------------
// Logic Info.
//-----------------------------------------------------------------------------

void Init();
void Update();
void Exit();
double GetTime();

_int64 previousCount;
LARGE_INTEGER previousCountLarge;
LARGE_INTEGER currentCount;
LARGE_INTEGER frequency;

double fixedTick;
double previousTime = 0.f;
double refreshTime = 0.f;
double elapsedTime = 0.f;

double frameRateCurrentTimer = 0.;
unsigned int numFrames = 0;
char buffer[5];
char buffer2[100];
char buffer3[100];

double realTime = 0.;
double logicRunTime = 0.;

const float ELAPSED_TIME_MAX = 1.f / 15.f;

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
	InitBalls(CORE_LoadPNG("data/tyrian_ball.png", false));
	InitRenderer();
	FONT_Init();
	QueryPerformanceCounter(&previousCountLarge);
	sprintf(buffer, "%d\n", numFrames);
	sprintf(buffer2, "%.2f\n", realTime);
	sprintf(buffer3, "%.2f\n", logicRunTime);
	previousCount = previousCountLarge.QuadPart;
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
		UpdateBalls();
		elapsedTime = elapsedTime - fixedTick;
		logicRunTime += fixedTick;
		SYS_Sleep(17); // To force 60 fps
	}
	UpdateRenderer();

	sprintf(buffer, "%.2f\n", 1./refreshTime);
	/*frameRateCurrentTimer += refreshTime;
	if (frameRateCurrentTimer >= 1)
	{
		sprintf(buffer, "%d\n", numFrames);
		frameRateCurrentTimer = 0;
		numFrames = 0;
	}
	else
	{
		++numFrames;
	}*/

	sprintf(buffer3, "LOGIC TIME: %.2f\n", logicRunTime);
	realTime = realTime + refreshTime;
	sprintf(buffer2, "REAL TIME: %.2f\n", realTime);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 20, SCR_HEIGHT - 25), buffer); //FPS print
	FONT_DrawString(vec2(20, 30), buffer2); //Real time print
	FONT_DrawString(vec2(20, 60), buffer3); //Logic time print

	//GENERAL FUNCTIONS
	// Exchanges the front and back buffers
	SYS_Show();
	SYS_Pump();	// Process Windows messages.
}

void Exit()
{
	ExitBall(CORE_LoadPNG("data/tyrian_ball.png", false));
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