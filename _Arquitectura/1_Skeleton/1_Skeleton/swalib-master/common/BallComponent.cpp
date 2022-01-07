#include "BallComponent.h"
#include "Entity.h"
#include "Time.h"
#include "Messages.h"

void BallComponent::Init(unsigned int _numArgs, va_list args)
{
	if (_numArgs == 2)
	{
		m_maxSpeed = va_arg(args, float);
		m_radius = va_arg(args, float);
	}
	root->GetTransform()->SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));	//= ;
	m_currentVel = vec2(CORE_FRand(-m_maxSpeed, m_maxSpeed), CORE_FRand(-m_maxSpeed, m_maxSpeed));
}


void BallComponent::Update()
{
	m_bufferPosition = root->GetTransform()->GetPosition();
	root->GetTransform()->SetPosition(m_bufferPosition + m_currentVel * TIME_DELTA_TIME);
	
	// Rebound on margins.
	if ((root->GetTransform()->GetPosition().x > SCR_WIDTH) || (root->GetTransform()->GetPosition().x < 0))
	{
		m_currentVel.x *= -1.0;
	}
	if ((root->GetTransform()->GetPosition().y > SCR_HEIGHT) || (root->GetTransform()->GetPosition().y < 0))
	{
		m_currentVel.y *= -1.0;
	}
}

void BallComponent::OnCollisionEnter()
{
	root->GetTransform()->SetPosition(m_bufferPosition);
	m_currentVel = m_currentVel * -1.f;
}

void BallComponent::Exit()
{

}

void BallComponent::RecieveMessage(Message* _message)
{
	OnCollisionEnter();
}