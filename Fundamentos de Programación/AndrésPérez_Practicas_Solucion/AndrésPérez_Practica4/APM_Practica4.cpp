// practica4.cpp
//
#include <stdio.h>
#include "consola.h"

struct TEntity;
typedef void (*FUNC_ENTITY)(TEntity*);


// ***************************************************************************************
// ENTIDAD
// ***************************************************************************************
struct TEntity
{
	int m_ix;
	int m_iy;
	FUNC_ENTITY* m_funcs;
	TEntity(FUNC_ENTITY* funcs, int x, int y)
	{
		m_ix = x;
		m_iy = y;
		m_funcs = funcs;
	}
};



void CheckLimits(TEntity* _pEntity)
{
	if(_pEntity->m_ix >= 10)
	{
		_pEntity->m_ix = 0;
	}
	else if(_pEntity->m_ix <= 0)
	{
		_pEntity->m_ix = 9;
	}

	if (_pEntity->m_iy >= 10)
	{
		_pEntity->m_iy = 0;
	}
	else if (_pEntity->m_iy <= 0)
	{
		_pEntity->m_iy = 9;
	}
}


#pragma region Draw
void DrawA(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("A");
}
void DrawB(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("B");
}
void DrawC(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("C");
}
void DrawD(TEntity* _pEntity)
{
	gotoxy(_pEntity->m_ix, _pEntity->m_iy);
	printf("D");
}
#pragma endregion

#pragma region Movimientos
//Desplazamientos rectos
void MoveUp(TEntity* _pEntity)
{
	_pEntity->m_iy += 1;
}

void MoveDown(TEntity* _pEntity)
{
	_pEntity->m_iy -= 1;
}

void MoveRight(TEntity* _pEntity)
{
	_pEntity->m_ix += 1;
}

void MoveLeft(TEntity* _pEntity)
{
	_pEntity->m_iy -= 1;
}

//Desplazamientos diagonales
void MoveUpRight(TEntity* _pEntity)
{
	_pEntity->m_iy += 1;
	_pEntity->m_ix += 1;
}

void MoveUpLeft(TEntity* _pEntity)
{
	_pEntity->m_iy += 1;
	_pEntity->m_ix -= 1;
}

void MoveDownRight(TEntity* _pEntity)
{
	_pEntity->m_iy -= 1;
	_pEntity->m_ix += 1;
}

void MoveDownLeft(TEntity* _pEntity)
{
	_pEntity->m_iy -= 1;
	_pEntity->m_ix -= 1;
}
#pragma endregion




// ***************************************************************************************
// MAIN
// ***************************************************************************************
unsigned int uKey;
int main(int argc, char* argv[])
{
	//Initialize FUNC_ENTITIES of each meep
	FUNC_ENTITY oFunc01[2] = { &MoveUp , &DrawA }; //Move then Draw, si no va un frame por detras
	FUNC_ENTITY oFunc02[2] = { &MoveDownLeft , &DrawD }; //Move then Draw, si no va un frame por detras
	FUNC_ENTITY oFunc03[2] = { &MoveRight, &DrawB}; //Move then Draw, si no va un frame por detras
	FUNC_ENTITY oFunc04[2] = { &MoveUpLeft , &DrawC }; //Move then Draw, si no va un frame por detras

	//Initialize entities
	TEntity tEnties[] =
	{
		TEntity(oFunc01, 0, 5),
		TEntity(oFunc02, 6, 9),
		TEntity(oFunc03, 3, 6), 
		TEntity(oFunc04, 2, 7) 
	};

	unsigned int const iSize = sizeof(tEnties) / sizeof(TEntity);

	//Update 
	while(true)
	{
		for(unsigned int i = 0; i < iSize; ++i)
		{
			//Move
			(*tEnties[i].m_funcs[0])(&tEnties[i]);
			CheckLimits(&tEnties[i]);

			//Draw
			(*tEnties[i].m_funcs[1])(&tEnties[i]);
		}
		hidecursor();
		Sleep(500);
		clear();
	}
}