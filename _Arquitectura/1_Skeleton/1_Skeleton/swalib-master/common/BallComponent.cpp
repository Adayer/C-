#include "BallComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"
#include "PlayerComponent.h"

void BallComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 4)
	{
		m_maxSpeed = va_arg(args, double);
		m_radius = va_arg(args, double);
		m_ballSize = va_arg(args, LogicManager::Size);
		vec2 initPos = va_arg(args, vec2);

		float xMax = (SCR_WIDTH - 200.0);
		float yMax = (SCR_HEIGHT - 200.0);

		root->GetTransform()->SetPosition(initPos);
		m_bufferPosition = initPos;

		m_currentVel = vec2(m_maxSpeed, m_maxSpeed);
	}
}
void BallComponent::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}
void BallComponent::InitExplodedBall(unsigned int _numArgs,...)
{
	va_list valist;
	va_start(valist, _numArgs);
	if (_numArgs == 4)
	{
		m_maxSpeed = va_arg(valist, double);
		m_radius = va_arg(valist, double);
		m_ballSize = va_arg(valist, LogicManager::Size);
		int isLeftBall = va_arg(valist, int);

		float xMult = isLeftBall ? -1.f : 1.f; //If is left ball moves to the left

		m_currentVel = vec2(m_maxSpeed * xMult, m_maxSpeed);
		m_bufferPosition = root->GetTransform()->GetPosition();
	}
	va_end(valist);
}

void BallComponent::Update()
{
	m_bufferPosition = root->GetTransform()->GetPosition(); //Buffer position is saved in case of collision
	double deltaTime = TIME_DELTA_TIME;
	vec2 newPos = m_bufferPosition + m_currentVel * TIME_DELTA_TIME;
	root->GetTransform()->SetPosition(newPos);	
}

//Moves the ball in the opposite direction of the entity it collided with
void BallComponent::OnEntityCollisionEnter(Entity* _otherEntity)
{
	vec2 vecBetweenPosUnit(root->GetTransform()->GetPosition() - _otherEntity->GetTransform()->GetPosition());
	vecBetweenPosUnit = vecBetweenPosUnit / (vlen(vecBetweenPosUnit));

	m_currentVel = vecBetweenPosUnit * m_maxSpeed;
	root->GetTransform()->SetPosition(m_bufferPosition + vecBetweenPosUnit * TIME_DELTA_TIME);
}

//Reflect velocity with the axis it collided into
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
	
	root->GetTransform()->SetPosition(m_bufferPosition + m_currentVel * TIME_DELTA_TIME);
}


void BallComponent::Exit()
{

}

//Breaks the ball in two if Size == (Big or Medium), Destroys the ball if size == Small
void BallComponent::Explode()
{
	switch (m_ballSize)
	{
	case LogicManager::Size::Big:
		{
			LOGIC_MANAGER_INSTANCE->DivideBall(root, m_ballSize);
			break;
		}
		case LogicManager::Size::Medium:
		{
			LOGIC_MANAGER_INSTANCE->DivideBall(root, m_ballSize);
			break;
		}
		case LogicManager::Size::Small:
		{
			LOGIC_MANAGER_INSTANCE->DestroyBall(root);
			break;
		}
	}
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
				if (entMsg->GetBallA()->FindComponent<PlayerComponent>()) //Checks if collided with player
				{
					Explode();
				}
				else 
				{
					OnEntityCollisionEnter(entMsg->GetBallA());
				}
			}
			else
			{
				if (entMsg->GetBallB()->FindComponent<PlayerComponent>()) //Checks if collided with player
				{
					Explode();
				}
				else
				{
					OnEntityCollisionEnter(entMsg->GetBallB());
				}
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