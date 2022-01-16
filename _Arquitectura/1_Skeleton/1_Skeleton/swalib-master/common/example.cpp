#pragma once

#include "EntityBank.h"
#include "font.h"
#include "EngineRenderer.h"
#include "InputManager.h"
#include "Managers.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"
#include <vector>
#include "World.h"

#include "core.h"


void Init();
void Update();
void Exit();

int Main(void)
{
	Init();	
  
	while (!SYS_GottaQuit() && !LogicManager::GetInstance()->GetEndGame()) {	// Controlling a request to terminate an application.
		Update();
	}

	Exit();

	return 0;
}

void Init() 
{
	EntityBank::GetInstance()->Init();
	World::GetInstance()->Init();
	InputManager::GetInstance()->Init();
	LogicManager::GetInstance()->Init();
	EngineRenderer::GetInstance()->InitRenderEngine();
	FONT_Init();
}


void Update()
{
	LogicManager::GetInstance()->Update();
	World::GetInstance()->Update();
	EngineRenderer::GetInstance()->UpdateRenderer(); //We update the Engine separately to ensure it updates after the logic
}

void Exit()
{
	FONT_End();
	EngineRenderer::GetInstance()->ExitRenderer();
	LogicManager::GetInstance()->Exit();
	InputManager::GetInstance()->Exit();
	World::GetInstance()->Exit();
	EntityBank::GetInstance()->Exit();
}