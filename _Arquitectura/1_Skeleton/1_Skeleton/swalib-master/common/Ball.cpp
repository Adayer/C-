#include "Ball.h"


void CBall::CreateBall()
{
	m_currentPos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
	m_currentVel = vec2(CORE_FRand(-m_maxSpeed, m_maxSpeed), CORE_FRand(-m_maxSpeed, m_maxSpeed));
}

void CBall::MoveBall(double _deltaTime, std::vector<CBall*> &_otherBalls, size_t _thisIndex)
{
	vec2 newpos = m_currentPos + m_currentVel * _deltaTime;

	// Collision detection.
	bool collision = false;
	int colliding_ball = -1;
	
	for (int j = 0; j < _otherBalls.size(); j++) 
	{
		if (j != _thisIndex)
		{
			float limit2 = (m_radius + _otherBalls[j]->GetRadius()) * (m_radius + _otherBalls[j]->GetRadius());
			if (vlen2(newpos - _otherBalls[j]->GetPosition()) <= limit2) 
			{
				collision = true;
				colliding_ball = j;
				break;
			}
		}
	}

	if (!collision) 
	{
		m_currentPos = newpos;
	}
	else 
	{
		// Rebound!
		m_currentVel = m_currentVel* -1.f;
		//_otherBalls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
	}

	// Rebound on margins.
	if ((m_currentPos.x > SCR_WIDTH) || (m_currentPos.x < 0)) 
	{
		m_currentVel.x *= -1.0;
	}
	if ((m_currentPos.y > SCR_HEIGHT) || (m_currentPos.y < 0)) 
	{
		m_currentVel.y *= -1.0;
	}
}

void CBall::UpdateBallRenderer()
{
	if (m_sprite)
	{
		m_sprite->SetPosition(m_currentPos);
		m_sprite->UpdateSpriteRender();
	}
}

void CBall::DestroyBall()
{
	if(m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}
}