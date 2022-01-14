#pragma once
#include "Character.h"

#include <vector>

class Bullet;
class Player : public Character
{

	//Variables
private:
	//New
	const int MAX_NUMBER_OF_BULLETS_PER_SIDE = 5; //Maximum number of bullets per side at any given point

	unsigned int m_iNumLeftBullets = 0; //Current amount of bullets shot to the left
	unsigned int m_iNumRightBullets = 0; //Current amount of bullets shot to the right

	//Funtions
public:
	//Overrides
	Player(int _pos, char _sprite) :
		Character(_pos, _sprite)
	{

	}

	//virtual void Init() override;
	virtual void Update() override;
	virtual void Exit() override;

	//virtual void MoveLeft() override;
	//virtual void MoveRight() override;

	virtual void Die() override;

	//New
	void ShootLeft(); //Spawns a bullet that moves to the left of the current position//Current amount of bullets shot to the left
	void ShootRight(); //Spawns a bullet that moves to the right of the current position//Current amount of bullets shot to the left

	void DestroyBullet(bool _fromRight); //Reduces pertinet counter

};
