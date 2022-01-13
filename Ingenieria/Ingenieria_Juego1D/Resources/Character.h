#pragma once
#include <vector>

#include "Entity.h"

//This clas doesn't implement any code, it serves to create a new parent class for entities that include a DIE Method
class Character : public Entity 
{
protected:
public:
	//Overrides
	Character(int _pos, char _sprite) :
		Entity(_pos, _sprite)
	{

	}
	//virtual void Init() override;
	//virtual void Update() override;
	//virtual void Exit() override;

	//virtual void MoveLeft() override;
	//virtual void MoveRight() override;

	//New 
	virtual void Die() {} //Implements functionality for Entity death
};
