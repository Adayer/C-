#include "Bullet.h"
#include "Player.h"

#include "../Singletons/GameLogic.h"

#include <Windows.h>
#include <Mmsystem.h>

void Player::Update()
{
	if (!m_isActive)
	{
		return;
	}
	//Inut
	//Movement variables
	short hInput = GetKeyState(0x48);
	short lInput = GetKeyState(0x4c);
	//Shooting variables
	short jInput = GetKeyState(0x4a);
	short kInput = GetKeyState(0x4b);
	if((hInput & 0x8000) != 0)
	{
		MoveLeft();
	}
	else if((lInput & 0x8000) != 0)
	{
		MoveRight();
	}
	else if ((jInput & 0x8000) != 0)
	{
		ShootLeft();
	}
	else if ((kInput & 0x8000) != 0)
	{
		ShootRight();
	}
	//Stop play input
	short escInput = GetKeyState(0x1b);
	if ((escInput & 0x8000) != 0)
	{
		GAME_MANAGER_INSTANCE->StopPlay();
	}
	
}

void Player::Exit()
{
	Die();

}

//Overrides
void Player::Die()
{
	PlaySound(TEXT("Data/muerte.wav"), NULL, SND_SYNC); //SND_SYNC to stop the game so the player realizes he has died
}

//New
void Player::ShootLeft() //Creates the bullet and adds it to Entities
{
	if (m_iNumLeftBullets < MAX_NUMBER_OF_BULLETS_PER_SIDE)
	{
		++m_iNumLeftBullets;
		Bullet* newBullet = new Bullet(m_iCurrentPosition  - 1,'<', false, this); //Memory deleted when Entity is removed
		GAME_MANAGER_INSTANCE->AddEntity(newBullet);
	}
}
void Player::ShootRight() //Creates the bullet and adds it to Entities 
{
	if (m_iNumRightBullets < MAX_NUMBER_OF_BULLETS_PER_SIDE)
	{
		++m_iNumRightBullets;
		Bullet* newBullet = new Bullet(m_iCurrentPosition  + 1,'>', true, this); //Memory deleted when Entity is removed
		GAME_MANAGER_INSTANCE->AddEntity(newBullet);
	}
}

void Player::DestroyBullet(bool _fromRight) //Reduces pertinet counter
{
	if (_fromRight)
	{
		--m_iNumRightBullets;
	}
	else
	{
		--m_iNumLeftBullets;
	}
}