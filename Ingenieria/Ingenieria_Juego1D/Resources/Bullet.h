#pragma once
#include "Entity.h"

class Player;
class Bullet : public Entity
{
	//Variables
private:
	bool m_bMovingRight = true; //True -> Right; False -> Left
	Player* m_pInstigator = nullptr; //The Player responsible for the bullet

	//Functions
public:
	Bullet(int _pos, char _sprite, bool _direction, Player* _instigator) :
		Entity(_pos, _sprite),
		m_bMovingRight(_direction),
		m_pInstigator(_instigator)
	{

	}
	//Overrides
	//virtual void Init() override;
	virtual void Update() override;//Has bool that calls either MoveLeft or MoveRight
	virtual void Exit() override;

	//virtual void MoveLeft() override;
	//virtual void MoveRight() override;

	//New
	void Hit(Entity* _hitEntity);//Is called when Entity is Hit
	void CheckCollision(); //Checks collisions with game boundaries and other enemies

	//Properties
	bool GetDirection() const { return m_bMovingRight; }
	void SetDirection(bool _direction) { m_bMovingRight = _direction; }


};
