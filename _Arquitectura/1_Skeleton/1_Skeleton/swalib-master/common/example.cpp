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
	InitBalls(CORE_LoadPNG("data/tyrian_ball.png", false));
	InitRenderer();
	FONT_Init();
}

void Update()
{
	UpdateBalls();
	UpdateRenderer();
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD!");

	//GENERAL FUNCTIONS
	// Exchanges the front and back buffers
	SYS_Show();
	SYS_Pump();	// Process Windows messages.
	SYS_Sleep(17);	// To force 60 fps
}

void Exit()
{
	ExitBall(CORE_LoadPNG("data/tyrian_ball.png", false));
	ExitRenderer();
	FONT_End();
}