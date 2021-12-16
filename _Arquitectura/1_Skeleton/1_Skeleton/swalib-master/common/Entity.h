#pragma once
#include <vector>

class Component;
class Transform;

class Entity
{
private:
	std::vector<Component*> m_tComponents;
	Transform* m_transform;
public:
	void AddComponent(Component*& _newComponent);
	
	template <class T>
	T* const FindComponent(); //Returns the first valid component of type T

	void Update(float _deltaTim); //Loops through all components and updates them all

	Entity();

	Transform* const GetTransform() { return m_transform; }
};