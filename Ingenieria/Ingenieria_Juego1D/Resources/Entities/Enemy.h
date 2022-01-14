#pragma once

#include "Character.h"

class Enemy: public Character
{
	//Variables
private:
	bool m_bMovingRight = true; //True -> Right; False -> Left

	//Functions
public:
	//Overrides
	Enemy(int _pos, char _sprite, bool _direction) :
		Character(_pos, _sprite),
		m_bMovingRight(_direction)
	{
		
	}

	//virtual void Init() override;
	virtual void Update() override; //Calls either MoveLeft or Right depending on bool
	virtual void Exit() override;

	//virtual void MoveLeft() override;
	//virtual void MoveRight() override;

	virtual void Die() override;

	//New
	void CheckCollision(); //Checks if the Enemy has collided with the player

	//Properties
	bool GetDirection() const { return m_bMovingRight; }
	void SetDirection(bool _direction) { m_bMovingRight = _direction; }

};
