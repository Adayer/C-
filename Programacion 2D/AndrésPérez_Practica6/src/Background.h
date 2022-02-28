#pragma once
#include "Sprite.h"
#include "vector2.h"

class Background
{
	//VARIABLES
private:
	const ltex_t* m_backgroundTexture = nullptr;
	float m_scrollRatio = 0;
	const vec2* m_scrollSpeed = nullptr;

	//FUNCTIONS
public:
	Background(const ltex_t* _text) : m_backgroundTexture(_text)
	{}
	
	const ltex_t* GetTexture() const { return m_backgroundTexture; }
	
	void SetScrollRatio(float _scrollRatio) { m_scrollRatio = _scrollRatio; }
	const float GetScrollRatio() const { return m_scrollRatio; }

	void SetScrollSpeed(const vec2& _speed) { m_scrollSpeed = &_speed; }
	const vec2& GetScrollSpeed() const { return *m_scrollSpeed; }

	void Update(float _deltaTime);
	void Draw(const vec2& _screenSize);
};