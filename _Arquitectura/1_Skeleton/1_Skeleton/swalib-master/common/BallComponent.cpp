#include "BallComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"

void BallComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 2)
	{
		m_maxSpeed = va_arg(args, double);
		m_radius = va_arg(args, double);
	}
	root->GetTransform()->SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));	
	m_speed = CORE_FRand(m_maxSpeed / 2, m_maxSpeed);
	m_currentVel = vec2(CORE_FRand(-m_maxSpeed, m_maxSpeed), CORE_FRand(-m_maxSpeed, m_maxSpeed));
	m_currentVel = m_currentVel / vlen(m_currentVel);
}


void BallComponent::Update()
{
	m_bufferPosition = root->GetTransform()->GetPosition();
	double deltaTime = TIME_DELTA_TIME;
	vec2 newPos = m_bufferPosition + m_currentVel * m_speed * TIME_DELTA_TIME;
	root->GetTransform()->SetPosition(newPos);	
}

void BallComponent::OnEntityCollisionEnter(Entity* _otherEntity)
{
	vec2 vecBetweenPosUnit(root->GetTransform()->GetPosition() - _otherEntity->GetTransform()->GetPosition());
	vecBetweenPosUnit = vecBetweenPosUnit / (vlen(vecBetweenPosUnit));

	m_currentVel = vecBetweenPosUnit;
	root->GetTransform()->SetPosition(m_bufferPosition + vecBetweenPosUnit * m_speed * TIME_DELTA_TIME);
}

void BallComponent::OnLimitCollisionEnter(bool isYAxis)
{
	if (isYAxis)
	{
		m_currentVel = vec2(m_currentVel.x , m_currentVel.y * -1.f);
	}
	else
	{
		m_currentVel = vec2(m_currentVel.x * -1.f, m_currentVel.y );
	}
	
	root->GetTransform()->SetPosition(m_bufferPosition + m_currentVel * m_speed * TIME_DELTA_TIME);
}


void BallComponent::Exit()
{

}

void BallComponent::RecieveMessage(Message* _message, Message::MessageType _typeOfMessage)
{
	
	switch (_typeOfMessage)
	{
		case(Message::MessageType::EntCollision):
		{
			EntCollisionMsg* entMsg = static_cast<EntCollisionMsg*>(_message);
			if (entMsg->GetBallA() != root)
			{
				OnEntityCollisionEnter(entMsg->GetBallA());
			}
			else
			{
				OnEntityCollisionEnter(entMsg->GetBallB());
			}
			break;
		}
		case(Message::MessageType::WorldLimit):
		{
			LimitWorldCollMsg* limitMsg = static_cast<LimitWorldCollMsg*>(_message);
			OnLimitCollisionEnter(limitMsg->GetYAxis());
			break;
		}
	}
	
}