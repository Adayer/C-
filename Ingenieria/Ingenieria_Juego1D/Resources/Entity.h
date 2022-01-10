#pragma once
#include <vector>

class Entity
{
protected:
	int m_iCurrentPosition = 0;
	char m_cRenderChar = '_';
public:
	Entity(int _pos, char _sprite) :
		m_iCurrentPosition(_pos),
		m_cRenderChar(_sprite)
	{

	}
	virtual void Init();
	virtual void Update();
	virtual void Exit();

	virtual void MoveLeft();
	virtual void MoveRight();

	int GetCurrentPosition() const { return m_iCurrentPosition; }
	char GetCharToRender() const{ return m_cRenderChar; }
};
