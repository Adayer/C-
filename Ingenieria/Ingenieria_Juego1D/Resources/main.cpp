#include "main.h"
#include "GameLogic.h"
#include "Renderer.h"

int main()
{
	Init();
	while (true)
	{
		Update();
	}
	Exit();
	return 0;
}

void Init()
{

}
void Update()
{
	GAME_MANAGER_INSTANCE->Update();
	RENDERER_INSTANCE->Update();
}
void Exit()
{

}
