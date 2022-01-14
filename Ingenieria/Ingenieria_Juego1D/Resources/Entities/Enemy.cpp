#include "Enemy.h"
#include "../Singletons/GameLogic.h"


void Enemy::Update()
{

	if (!m_isActive)
	{
		return;
	}
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

void Enemy::Exit()
{
	Die();
}

void Enemy::Die()
{
	GAME_MANAGER_INSTANCE->RemoveEnemy(this);
}

void Enemy::CheckCollision()
{

	if (m_iCurrentPosition == GAME_MANAGER_INSTANCE->GetPlayerPosition())
	{
		GAME_MANAGER_INSTANCE->EndGame();
	}
	//Needs to check if previous position was ocupied by Enemy to ensure the enemy did not overlap with the bullet at anypoint
	else if (m_bMovingRight && (m_iCurrentPosition - 1) == GAME_MANAGER_INSTANCE->GetPlayerPosition())
	{
		GAME_MANAGER_INSTANCE->EndGame();
	}
	//Needs to check if previous position was ocupied by Enemy to ensure the enemy did not overlap with the bullet at anypoint
	else if (!m_bMovingRight && (m_iCurrentPosition + 1) == GAME_MANAGER_INSTANCE->GetPlayerPosition())
	{
		GAME_MANAGER_INSTANCE->EndGame();
	}
}