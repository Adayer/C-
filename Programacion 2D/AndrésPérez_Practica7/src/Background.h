#pragma once
#include "Sprite.h"
#include "vector2.h"

class Background
{
	//VARIABLES
private:
	const ltex_t* m_backgroundTexture = nullptr;
	float m_scrollRatio = 0.5f;
	vec2 m_scrollSpeed;
	vec2 m_bufferCameraPos;
	
	float u0 = 0.f;
	float u1 = 0.f;
	float v0 = 1.f;
	float v1 = 1.f;

	int m_numReplicationsX;
	int m_numReplicationsY;

	//FUNCTIONS
public:
	Background(const ltex_t* _text, float _ratio, int _replicationsX, int _replicationsY) :
		m_backgroundTexture(_text),
		m_scrollRatio(_ratio),
		m_scrollSpeed(0.f, 0.f),
		m_numReplicationsX(_replicationsX),
		m_numReplicationsY(_replicationsY),
		u0(0.f),
		v0(0.f),
		u1(_replicationsX),
		v1(_replicationsY),
		m_bufferCameraPos(400.f, 0.f)
	{}
	
	const ltex_t* GetTexture() const { return m_backgroundTexture; }
	
	void SetScrollRatio(float _scrollRatio) { m_scrollRatio = _scrollRatio; }
	const float GetScrollRatio() const { return m_scrollRatio; }

	void SetScrollSpeed(const vec2& _speed) { m_scrollSpeed = _speed; }
	const vec2& GetScrollSpeed() const { return m_scrollSpeed; }

	void Update(float _deltaTime, const vec2& _cameraPos);
	void Draw(const vec2& _screenSize, const vec2& _cameraPos);
};