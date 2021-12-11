#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"

class EngineRenderer
{
private:
	//Singleton variables
	static EngineRenderer* instance;
	EngineRenderer() {}
public:
	//Singleton variables
	static EngineRenderer* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new EngineRenderer();
		}
		return instance;
	}

	//To assure singleton is not copied or created using a copy
	EngineRenderer(EngineRenderer& other) = delete;
	void operator=(const EngineRenderer&) = delete;

	//Initialize render
	void InitRenderEngine();
};


class CSprite
{
protected:
	GLuint m_sprite; //The sprite's texture to represent
	vec2 m_size; //Size
	vec2 m_position; //Current screen position
public:
	CSprite(GLuint _texture, vec2 _size, vec2 _position) :
		m_sprite(_texture), 
		m_size(_size), 
		m_position(_position) 
	{
		
	}
	GLuint GetTexture() { return m_sprite; }
	void SetTexture(GLuint _sprite) { m_sprite = _sprite; }

	const vec2 GetSize() { return m_size; }
	void SetSize(const vec2 _size) { m_size = _size; }

	const vec2 GetPosition() { return m_position; }
	void SetPosition(const vec2 _position) { m_position = _position; }

	void virtual UpdateSpriteRender(); //Render the sprite
};

//Class that renders sprites that can be tiled across the whole window
class CTileableSprite : public CSprite
{
	int m_tileWidth = 0; //Tile width
	int m_tileHeight = 0; //Tile height

public:
	CTileableSprite(GLuint _texture, vec2 _size, vec2 _position, int _width, int _height) : 
		CSprite(_texture, _size, _position),
		m_tileWidth(_width),
		m_tileHeight(_height)
	{

	}
	void UpdateSpriteRender() override;
};