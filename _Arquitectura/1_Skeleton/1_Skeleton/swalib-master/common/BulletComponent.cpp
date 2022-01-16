#include "BulletComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"
#include "BallComponent.h"
#include "World.h"

void BulletComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 1)
	{
		m_speed = va_arg(args, double);
	}
}
void BulletComponent::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}

void BulletComponent::Update()
{
	root->GetTransform()->SetPosition(vec2(root->GetTransform()->GetPosition().x, root->GetTransform()->GetPosition().y + m_speed * TIME_DELTA_TIME));
}

void BulletComponent::OnEntityCollisionEnter(Entity* _otherEntity)
{
	if (_otherEntity->FindComponent<BallComponent>()) //Checks if collided with ball
	{
		_otherEntity->FindComponent<BallComponent>()->Explode();
		World::GetInstance()->RemoveEntity(root);
	}
}

void BulletComponent::OnLimitCollisionEnter(bool isYAxis) //Destroys the entity
{
	World::GetInstance()->RemoveEntity(root);
}

void BulletComponent::Exit()
{
	
}

void BulletComponent::RecieveMessage(Message* _message, Message::MessageType _typeOfMessage)
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