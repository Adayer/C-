#pragma once
#include "vector2d.h"
#include <stdarg.h>
class Entity;

class Component
{
protected:
	Entity* root; //El padre
public:
	virtual void Init(unsigned int _numArgs, va_list args) = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
	Component(Entity* _root): root(_root){}
};

class Transform : public Component
{
private:
	vec2 m_position;
	vec2 m_scale;
	float m_rotation;
public:
	Transform(Entity* _root): Component(_root),
		m_position(0.f,0.f),
		m_scale(1.f, 1.f),
		m_rotation(0.f) 
	{}

	virtual void Init(unsigned int _numArgs, va_list args) override 
	{
		if (_numArgs == 3)
		{
			m_position = va_arg(args, vec2);
			m_scale = va_arg(args, vec2);
			m_rotation = va_arg(args, float);
		}
	}

	void Update() override {}
	void Exit() override {}

	const vec2 GetPosition() { return m_position; }
	void SetPosition(vec2 _newPos) { m_position = _newPos; }

	const vec2 GetScale() { return m_scale; }
	void SetScale(vec2 _newScale) { m_scale = _newScale; }

	const float GetRotation() { return m_rotation; }
	void SetScale(float _newRotation) { m_scale = _newRotation; }

};