#include <windows.h>

#include "Renderer.h"
#include "GameLogic.h"

#include "../Entities/Entity.h"


Renderer* Renderer::instance = nullptr;

void Renderer::Init()
{
	//Currently no values need to be initialized
}
void Renderer::Update()
{
	Clear();
	//Draw the Game field
	MoveCursorToX(0);
	const unsigned int sizeOfGame = GAME_MANAGER_INSTANCE->GetSize();
	for (unsigned int i = 0; i <= sizeOfGame; ++i)
	{
		printf("_");
	}
	//Draw the score
	printf(" %d - %d\n", GAME_MANAGER_INSTANCE->GetPlayerKills(), GAME_MANAGER_INSTANCE->GetPlayerDeaths());

	//Draw each of the entities
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
	//Currently no exit configuration is needed
}

void Renderer::MoveCursorToX(int x)
{
	COORD pos = { x, 1 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void Renderer::Clear()
{
	system("cls");
}
	
