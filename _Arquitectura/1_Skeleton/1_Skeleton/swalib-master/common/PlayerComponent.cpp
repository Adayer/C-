#include "PlayerComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"
#include "Managers.h"
#include "BallComponent.h"
#include "sys.h"

#define ROOT_POSITION root->GetTransform()->GetPosition()

void PlayerComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 5)
	{
		m_vPlayerInitPosition = va_arg(args, vec2);
		m_iMaxLives = va_arg(args, int);
		m_fPlayerSpeed = va_arg(args, double);
		m_fullLifeSprite = va_arg(args, GLuint*);
		m_emptyLifeSprite = va_arg(args, GLuint*);
	}
	
	m_iCurrentLives = m_iMaxLives;
	
	root->GetTransform()->SetPosition(m_vPlayerInitPosition);
	

	//Bind movement functions to InputManager
	InputManager::GetInstance()->RegisterOnLeftPressed(std::bind(&PlayerComponent::MoveLeft,this));
	InputManager::GetInstance()->RegisterOnRightPressed(std::bind(&PlayerComponent::MoveRight,this));
}
void PlayerComponent::Init(unsigned int _numArgs, ...)
{
	va_list valist;
	va_start(valist, _numArgs);
	Init(_numArgs, valist);
	va_end(valist);
}


void PlayerComponent::Update()
{

}

void PlayerComponent::Exit()
{

}

void PlayerComponent::OnCollisionEnter()
{
	--m_iCurrentLives;
	m_tLivesSprites[m_iCurrentLives]->SetTexture(m_emptyLifeSprite); //Changes life texture to emptyHeart
	if (m_iCurrentLives <= 0)
	{
		LogicManager::GetInstance()->EndGame();
	}
}

void PlayerComponent::RecieveMessage(Message* _message, Message::MessageType _typeOfMessage)
{
	if (_typeOfMessage == Message::MessageType::EntCollision)
	{
		EntCollisionMsg* entMsg = static_cast<EntCollisionMsg*>(_message);
		if (entMsg->GetBallA() != root)
		{
			if (entMsg->GetBallA()->FindComponent<BallComponent>()) //Checks if other entity is a ball
			{
				OnCollisionEnter();
			}
		}
		else
		{
			if (entMsg->GetBallB()->FindComponent<BallComponent>()) //Checks if other entity is a ball
			{
				OnCollisionEnter();
			}
		}
	}
}

void PlayerComponent::MoveLeft()
{
	float newXPos = ROOT_POSITION.x - m_fPlayerSpeed * TIME->DeltaTime();

	if (newXPos < 33)
	{
		newXPos = 33;
	}

	root->GetTransform()->SetPosition(vec2(newXPos, ROOT_POSITION.y));
}

void PlayerComponent::MoveRight()
{
	float newXPos = ROOT_POSITION.x + m_fPlayerSpeed * TIME->DeltaTime();

	if (newXPos > (SCR_WIDTH - 33))
	{
		newXPos = (SCR_WIDTH - 33);
	}

	root->GetTransform()->SetPosition(vec2(newXPos, ROOT_POSITION.y));
}