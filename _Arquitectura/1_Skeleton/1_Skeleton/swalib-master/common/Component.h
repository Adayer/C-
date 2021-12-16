#pragma once
class Entity;

class Component
{
protected:
	Entity* root; //El padre
public:
	virtual void Update() = 0;
	Component(Entity* _root): root(_root){}
};

class Transform : public Component
{
public:
	void Update() override {}
	Transform(Entity* _root): Component(_root){}
};