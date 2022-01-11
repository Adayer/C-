#include "Player.h"
#include <Windows.h>

void Player::Update()
{
	short aInput = GetKeyState(0x41);
	short dInput = GetKeyState(0x44);
	if((aInput & 0x8000) != 0)
	{
		MoveLeft();
	}
	else if((dInput & 0x8000) != 0)
	{
		MoveRight();
	}
}

//Overrides
void Player::Die()
{

}

//New
void Player::ShootLeft()
{

}
void Player::ShootRight() 
{

}