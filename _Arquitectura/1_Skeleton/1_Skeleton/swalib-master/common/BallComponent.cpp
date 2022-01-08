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
	root->GetTransform()->SetPosition(vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT)));	//= ;
	m_currentVel = vec2(CORE_FRand(-m_maxSpeed, m_maxSpeed), CORE_FRand(-m_maxSpeed, m_maxSpeed));
}


void BallComponent::Update()
{
	m_bufferPosition = root->GetTransform()->GetPosition();
	double deltaTime = TIME_DELTA_TIME;
	vec2 newPos = m_bufferPosition + m_currentVel * TIME_DELTA_TIME;
	root->GetTransform()->SetPosition(newPos);	
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