#include "Enemy.h"
#include "GameLogic.h"

void Enemy::Update()
{
	CheckCollision(); //Collision needs to be checked before and after movement just in case the player has already moved into the enmies position
	if(m_bMovingRight)
	{
		MoveRight();
	}
	else
	{
		MoveLeft();
	}

	CheckCollision();
}

void Enemy::CheckCollision()
{
	if (m_iCurrentPosition == GAME_MANAGER_INSTANCE->GetPlayerPosition())
	{
		GAME_MANAGER_INSTANCE->EndGame();
	}
}