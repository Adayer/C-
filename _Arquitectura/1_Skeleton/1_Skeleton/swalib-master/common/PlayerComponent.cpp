#include "PlayerComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"
#include "Managers.h"

#include "sys.h"

#define ROOT_POSITION root->GetTransform()->GetPosition()

void PlayerComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 2)
	{
		m_vPlayerInitPosition = va_arg(args, vec2);
		m_fPlayerSpeed = va_arg(args, double);
	}
	root->GetTransform()->SetPosition(m_vPlayerInitPosition);
	
	InputManager::GetInstance()->RegisterOnLeftPressed(std::bind(&PlayerComponent::MoveLeft,this));
	InputManager::GetInstance()->RegisterOnRightPressed(std::bind(&PlayerComponent::MoveRight,this));
}


void PlayerComponent::Update()
{

}

void PlayerComponent::Exit()
{

}

void PlayerComponent::OnCollisionEnter()
{
	
}

void PlayerComponent::RecieveMessage(Message* _message, Message::MessageType _typeOfMessage)
{
	OnCollisionEnter();
}

void PlayerComponent::MoveLeft()
{
	float newXPos = ROOT_POSITION.x - m_fPlayerSpeed * TIME->DeltaTime();

	if (newXPos < 10)
	{
		newXPos = 10;
	}

	root->GetTransform()->SetPosition(vec2(newXPos, ROOT_POSITION.y));
}

void PlayerComponent::MoveRight()
{
	float newXPos = ROOT_POSITION.x + m_fPlayerSpeed * TIME->DeltaTime();

	if (newXPos > (SCR_WIDTH - 10))
	{
		newXPos = (SCR_WIDTH - 10);
	}

	root->GetTransform()->SetPosition(vec2(newXPos, ROOT_POSITION.y));
}