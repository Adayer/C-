#include <windows.h>

#include "Renderer.h"
#include "GameLogic.h"
#include "Entity.h"


Renderer* Renderer::instance = nullptr;

void Renderer::Init()
{
	
}
void Renderer::Update()
{
	Clear();
	MoveCursorToX(0);
	const unsigned int sizeOfGame = GAME_MANAGER_INSTANCE->GetSize();
	for (unsigned int i = 0; i < sizeOfGame; ++i)
	{
		printf("_");
	}
	printf(" 0 - 0\n");

	std::vector<Entity*>* pToEntities = GAME_MANAGER_INSTANCE->GetEntities();
	if (pToEntities)
	{
		size_t numEntities = GAME_MANAGER_INSTANCE->GetEntities()->size();
		for (size_t i = 0; i < numEntities; ++i)
		{
			MoveCursorToX((*pToEntities)[i]->GetCurrentPosition());
			printf("%c", (*pToEntities)[i]->GetCharToRender());
		}
	}
}
void Renderer::Exit()
{

}

void Renderer::MoveCursorToX(int x)
{
	COORD pos = { x, 1 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void Renderer::HideCursor(void) {
	HANDLE hdl;
	hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO t;
	t.bVisible = false;
	SetConsoleCursorInfo(hdl, &t);
}

void Renderer::Clear()
{
	system("cls");
}
	
