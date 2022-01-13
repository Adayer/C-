#include "main.h"
#include "GameLogic.h"
#include "Renderer.h"

#include <chrono>
#include <thread>

std::chrono::milliseconds timespan(330); // Time between frames

int main()
{
	Init();
	while (GAME_MANAGER_INSTANCE->KeepPlaying())
	{
		Update();
	}
	Exit();
	return 0;
}

void Init()
{
	GAME_MANAGER_INSTANCE->Init();
	RENDERER_INSTANCE->Init();
}
void Update()
{
	GAME_MANAGER_INSTANCE->Update();
	RENDERER_INSTANCE->Update();

	std::this_thread::sleep_for(timespan);
}
void Exit()
{
	GAME_MANAGER_INSTANCE->Exit();
	RENDERER_INSTANCE->Exit();
}
