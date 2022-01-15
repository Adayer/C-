#include "Entity.h"
#include "Messages.h"
#include <stdarg.h>
#include <iterator>

Entity::Entity()
{
	AddComponent<Transform>(m_transform, 3, vec2(0.f,0.f), vec2(1.f, 1.f), 0.f);
	m_isActive = false;
}
Entity::~Entity()
{
	Exit();
	int iSize = m_tComponents.size();
	for (int i = (iSize - 1); i >= 0; --i)
	{
		delete m_tComponents[i];
		m_tComponents.pop_back();
	}
}

void Entity::Exit()
{
	int iSize = m_tComponents.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_tComponents[i]->Exit();
	}
}

void Entity::Update(float deltaTime)
{
	if (!m_isActive)
	{
		return;
	}
	size_t iSize = m_tComponents.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_tComponents[i])
		{
			m_tComponents[i]->Update();
		}
	}
}

void Entity::SendMessage(Message* _message, Message::MessageType _messageType)
{
	if (!m_isActive)
	{
		return;
	}
	std::vector<Component*>::iterator iter;
	for (iter = m_tComponents.begin(); iter != m_tComponents.end(); ++iter)
	{
		(*iter)->RecieveMessage(_message, _messageType);
	}
}