#pragma once
#include "Entity.h"

class Bullet : public Entity
{
private:
	bool m_bMovingRight = true; //True -> Right; False -> Left
public:
	Bullet(int _pos, char _sprite, bool _direction) :
		Entity(_pos, _sprite),
		m_bMovingRight(_direction)
	{

	}
	//Overrides
	void Init();
	void Update();//Has bool that calls either MoveLeft or MoveRight
	void Exit();

	void MoveLeft();
	void MoveRight();

	//New
	void Hit(Entity* _hitEntity);//Is called when Character is Hit

	bool GetDirection() const { return m_bMovingRight; }
	void SetDirection(bool _direction) { m_bMovingRight = _direction; }

};
