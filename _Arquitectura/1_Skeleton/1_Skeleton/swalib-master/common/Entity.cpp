#include "Entity.h"
#include "Messages.h"
#include <stdarg.h>
#include <iterator>

Entity::Entity()
{
	AddComponent<Transform>(m_transform, 3, vec2(0.f,0.f), vec2(1.f, 1.f), 0.f);
}
Entity::~Entity()
{
	int iSize = m_tComponents.size();
	for (int i = iSize; i >= 0; --i)
	{
		m_tComponents[i]->Exit();
		delete m_tComponents[i];
		m_tComponents.pop_back();
	}
}

void Entity::Update(float deltaTime)
{
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
	std::vector<Component*>::iterator iter;
	for (iter = m_tComponents.begin(); iter != m_tComponents.end(); ++iter)
	{
		(*iter)->RecieveMessage(_message, _messageType);
	}
}