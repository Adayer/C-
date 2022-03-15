#pragma once
#include <cmath>
class Player
{
public:
	const float GRAVITY = 98.f;
	const float MAX_HORIZONTAL_VELOCITY = 100.f;
	const float MIN_VERTICAL_VELOCITY = -150.f;
	const float MAX_VERTICAL_VELOCITY = 100.f;
	const float JUMP_VELOCITY = -500.f;
private:
	float m_fCurrentYSpeed = 0.f;
public:
	float GetCurrentYSpeed() { return m_fCurrentYSpeed; }
	void SetCurrentYSpeed(float _speed) 
	{
		if (_speed < MIN_VERTICAL_VELOCITY)
		{
			_speed = MIN_VERTICAL_VELOCITY;
		}
		else if (_speed > MAX_VERTICAL_VELOCITY)
		{
			_speed = MAX_VERTICAL_VELOCITY;
		}
		m_fCurrentYSpeed = _speed;
	}
};