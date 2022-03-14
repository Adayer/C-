#pragma once
#include <cmath>
class Player
{
public:
	const float GRAVITY = -9.8f;
	const float MAX_HORIZONTAL_VELOCITY = 100.f;
	const float MAX_VERTICAL_VELOCITY = 100.f;
	const float JUMP_VELOCITY = 50.f;
private:
	float m_fCurrentYSpeed = 0.f;
public:
	float GetCurrentYSpeed() { return m_fCurrentYSpeed; }
	void SetCurrentYSpeed(float _speed) 
	{
		if (abs(_speed) <= MAX_VERTICAL_VELOCITY)
		{
			m_fCurrentYSpeed = _speed; 
		}
		else
		{
			m_fCurrentYSpeed = (_speed < 0) ? -MAX_VERTICAL_VELOCITY : MAX_VERTICAL_VELOCITY;
		}
	}
};