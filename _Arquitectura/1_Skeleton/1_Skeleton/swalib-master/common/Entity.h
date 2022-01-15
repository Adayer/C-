#pragma once
#include <vector>
#include <assert.h>
#include <stdarg.h>
#include "Component.h"


//class Component;
//class Transform;

class Message;

class Entity
{
private:
	std::vector<Component*> m_tComponents;
	Transform* m_transform; // Al entities have a Transform component
public:

	void Init(); //Initialize the Entity
	void Update(float _deltaTim); //Loops through all components and updates them all
	void Exit() {}; //Prepares the Entity for destruction

	void SendMessage(Message* _message, Message::MessageType _messageType); //Sends a message to all components

	Entity();
	~Entity();

	Transform* const GetTransform() { return m_transform; }

	std::vector<Component*>* GetComponentList() { return &m_tComponents; }

	template <class T>
	T* const FindComponent() //Returns pointer to the first valid component of type T
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

		return nullptr; //T was not a valid component or T was not found
	}

	//NEEDS TO BE CHECKED;
	//Add Component function and overloads
	template <class T>
	void AddComponent() //Adds a new component to the Entity
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<Component*>(newComp);

		if (pComp)
		{
			m_tComponents.push_back(pComp);
			pComp->Init();//INIT NEEDS TO BE CHECKED;
		}
		else
		{
			assert(0); //T was not a component
		}
	}
	
	template <class T>
	void AddComponent(unsigned int _numArgs, ...) //Adds a new component to the Entity and initializes it with inputed values
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<Component*>(newComp);

		if (pComp)
		{
			va_list valist;
			va_start(valist, _numArgs);

			m_tComponents.push_back(pComp);
			pComp->Init(_numArgs, valist); //INIT NEEDS TO BE CHECKED;

			va_end(valist);
		}
		else
		{
			assert(0); //T was not a component
		}
	}

	template <class T>
	void AddComponent(T*& pointerOut_)//Adds a new component to the Entity and returns pointer to component
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<Component*>(newComp);

		if (pComp)
		{
			m_tComponents.push_back(pComp);
			pComp->Init();//INIT NEEDS TO BE CHECKED;
		}
		else
		{
			assert(0); //T was not a component
		}

		pointerOut_ = newComp;
	}

	template <class T>
	void AddComponent(T*& pointerOut_, unsigned int _numArgs, ...)//Adds a new component to the Entity and returns pointer to component and initializes it with inputed values
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<Component*>(newComp);

		if (pComp)
		{
			va_list valist;
			va_start(valist, _numArgs);

			m_tComponents.push_back(pComp);
			pComp->Init(_numArgs, valist); //INIT NEEDS TO BE CHECKED;
			
			va_end(valist);

		}
		else
		{
			assert(0); //T was not a component
		}

		pointerOut_ = newComp;
	}
};