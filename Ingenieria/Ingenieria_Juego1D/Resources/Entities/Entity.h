#pragma once
#include <vector>

//This is the parent class for all game entities
class Entity
{
	//Variables
protected:
	int m_iCurrentPosition = 0; //Current position
	char m_cRenderChar = '_'; //Tile render char
public:
	bool m_isActive = true; //If false the entity won't update

	//Funtions
public:
	Entity(int _pos, char _sprite) :
		m_iCurrentPosition(_pos),
		m_cRenderChar(_sprite)
	{

	}
	virtual void Init(); //Initialize method
	virtual void Update(); //Called by GameLogic to update entity
	virtual void Exit(); //Prepares the Entity for deletion

	virtual void MoveLeft(); //Moves the entity one square to the left
	virtual void MoveRight(); //Moves the entity one square to the right

	//Properties
	int GetCurrentPosition() const { return m_iCurrentPosition; }
	char GetCharToRender() const{ return m_cRenderChar; }
};
