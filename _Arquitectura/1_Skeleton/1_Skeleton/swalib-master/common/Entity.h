#pragma once
#include <vector>
#include <assert.h>
#include <stdarg.h>

class Component;
class Transform;

class Entity
{
private:
	std::vector<Component*> m_tComponents;
	Transform* m_transform; // Al entities have a Transform component
	~Entity();
public:

	void Init(); //Initialize the Entity
	void Update(float _deltaTim); //Loops through all components and updates them all
	void Exit(); //Prepares the Entity for destruction

	Entity();

	Transform* const GetTransform() { return m_transform; }

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

		assert(0); //T was not a valid component
	}

	//Add Component function and overloads
	template <class T>
	void AddComponent() //Adds a new component to the Entity
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<CPadre*>(newComp);

		if (pComp)
		{
			m_tComponents.push_back(pComp);
			pComp->Init();
		}
		else
		{
			assert(0) //T was not a component
		}
	}
	
	template <class T>
	void AddComponent(unsigned int _numArgs, ...) //Adds a new component to the Entity and initializes it with inputed values
	{
		T* newComp = new T(this);
		Component* pComp = dynamic_cast<CPadre*>(newComp);

		if (pComp)
		{
			va_list valist;
			va_start(valist, _numArgs);

			m_tComponents.push_back(pComp);
			pComp->Init();

			va_end(valist);
		}
		else
		{
			assert(0) //T was not a component
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
			m_tComponents.push_back(pComp);
		}
		else
		{
			assert(0); //T was not a component
		}

		pointerOut_ = newComp;
	}
};