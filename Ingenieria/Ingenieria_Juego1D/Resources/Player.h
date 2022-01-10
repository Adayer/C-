#pragma once
#include <vector>

#include "Character.h"

class Bullet;
class Player : public Character
{
private:
	//New
	const int MAX_NUMBER_OF_BULLETS_PER_SIDE = 5;
	std::vector<Bullet*> m_tLeftBullets;
	std::vector<Bullet*> m_tRightBullets;
public:
	//Overrides
	Player(int _pos, char _sprite) :
		Character(_pos, _sprite)
	{

	}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Exit() override;

	virtual void MoveLeft() override;
	virtual void MoveRight() override;

	virtual void Die() override;

	//New
	void ShootLeft();
	void ShootRight();
};
