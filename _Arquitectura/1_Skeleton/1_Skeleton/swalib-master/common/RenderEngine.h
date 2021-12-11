#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"

//class CRenderEngine 
//{
//private: 
//	static CRenderEngine* instance;
//	CRenderEngine() {}
//public:
//	static CRenderEngine* GetInstance()
//	{
//		if (instance == nullptr)
//		{
//			instance = new CRenderEngine();
//		}
//		return instance;
//	}
//		
//	//To assure RenderEngine is not copied or created using a copy
//	CRenderEngine(CRenderEngine& other) = delete;
//	void operator=(const CRenderEngine&) = delete;
//
//	void InitRenderEngine();
//};

//class CSprite
//{
//private:
//	const GLuint* m_sprite;
//	vec2 m_size;
//	vec2 m_position;
//public: 
//	CSprite(GLuint* _texture, vec2 _size, vec2 _position) : 
//		m_sprite(_texture), 
//		m_size(_size), 
//		m_position(_position) 
//	{
//
//	}
//
//	const GLuint* GetTexture() { return m_sprite; }
//	void SetTexture(const GLuint* _sprite) { m_sprite = _sprite; }
//
//	const vec2 GetSize() { return m_size; }
//	void SetSize(const vec2 _size) { m_size = _size; }
//
//	const vec2 GetPosition() { return m_position; }
//	void SetPosition(const vec2 _position) { m_position = _position; }
//
//	void UpdateSpriteRender();
//};