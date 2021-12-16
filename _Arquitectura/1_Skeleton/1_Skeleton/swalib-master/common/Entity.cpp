#include "Entity.h"
#include "Component.h"
#include <assert.h>


Entity::Entity()
{
	Component* transform = new Transform(this);
	AddComponent(transform);
	m_transform = static_cast<Transform*>(transform);
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

void Entity::AddComponent(Component*& _newComponent)
{
	m_tComponents.push_back(_newComponent);
}

template <class T>
T* const Entity::FindComponent()
{
	size_t iSize = m_tComponents.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		T* pComp = dynamic_cast<T*>(m_tComponents[i]); //If the component is not of type T, pComp == nullptr
		if (pComp)
		{
			return pComp; //Returns the first valid component
		}
	}

	assert(0); //T was not a valid component
}