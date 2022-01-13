#include "Bullet.h"
#include "GameLogic.h"
#include "Player.h"

void Bullet::Update()
{

	if (!m_isActive)
	{
		return;
	}

	if (m_bMovingRight)
	{
		MoveRight();
	}
	else
	{
		MoveLeft();
	}

	CheckCollision(); //Checks collisions after movement to ensure no deleted memory is used on the second pass
}

void Bullet::Exit()
{
	m_pInstigator->DestroyBullet(m_bMovingRight); //Tells the player the bullet has been destroyed
	GAME_MANAGER_INSTANCE->RemoveEntity(this); //Prepares the bullet for deletion
}


void Bullet::Hit(Entity* _hitEntity)
{
	_hitEntity->Exit(); //Calls Exit method of other entity
	Exit();
}

//Macro for readability 
#define GM_ENEMIES GAME_MANAGER_INSTANCE->GetEnemies() 
void Bullet::CheckCollision()
{
	size_t numEntities = GAME_MANAGER_INSTANCE->GetEnemies()->size();
	for (size_t i = 0; i < numEntities; ++i)
	{
		if((*GM_ENEMIES)[i]->GetCurrentPosition() == m_iCurrentPosition) 
		{
			Hit((*GM_ENEMIES)[i]);
			return;
		}
		//Needs to check if previous position was ocupied by Enemy to ensure the enemy did not overlap with the bullet at anypoint
		else if (m_bMovingRight && (*GM_ENEMIES)[i]->GetCurrentPosition() == (m_iCurrentPosition - 1)) 
		{
			Hit((*GM_ENEMIES)[i]);
			return;
		}
		//Needs to check if previous position was ocupied by Enemy to ensure the enemy did not overlap with the bullet at anypoint
		else if (!m_bMovingRight && (*GM_ENEMIES)[i]->GetCurrentPosition() == (m_iCurrentPosition  + 1))
		{
			Hit((*GM_ENEMIES)[i]);
			return;
		}
	}

	//Out of Boundaries check
	if (m_iCurrentPosition < 1 || m_iCurrentPosition > GAME_MANAGER_INSTANCE->GetSize()) 
	{
		Exit();
	}
}