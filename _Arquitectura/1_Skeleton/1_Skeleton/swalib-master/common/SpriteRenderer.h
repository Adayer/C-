#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"
#include "Component.h"
#include "EngineRenderer.h"

class SpriteRenderer : public Component
{
protected:
	GLuint* m_sprite; //The sprite's texture to represent
	vec2 m_size; //Size
public:
	SpriteRenderer(Entity* _root) :
		Component(_root),
		m_sprite(0),
		m_size(0,0)
	{
	}

	GLuint* GetTexture() { return m_sprite; }
	void SetTexture(GLuint* _sprite) { m_sprite = _sprite; }

	const vec2 GetSize() { return m_size; }
	void SetSize(const vec2 _size) { m_size = _size; }

	//(3, m_sprite, m_size, RenderLayer)
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override {} //Does nothing as is updated by Engine
	virtual void Exit() override {}

	void virtual UpdateRender(); //Render the sprite (called by Engine)
	virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override {}
};

//I think currently unused afte background sprite change
//Class that renders sprites that can be tiled across the whole window
class TileableSpriteRenderer : public SpriteRenderer
{
	float m_tileWidth = 0; //Tile width
	float m_tileHeight = 0; //Tile height

public:
	TileableSpriteRenderer(Entity* _root) :
		SpriteRenderer(_root),
		m_tileWidth(0),
		m_tileHeight(0)
	{

	}

	//(5, m_sprite, m_size, RenderLayer ,m_tileWidth, m_tileHeight)
	virtual void Init(unsigned int _numArgs, va_list args) override;
	virtual void Init(unsigned int _numArgs, ...) override;
	virtual void Init() override {}
	virtual void Update() override {} //Does nothing as is updated by Engine
	virtual void Exit() override {}

	virtual void UpdateRender() override;
	//virtual void RecieveMessage(Message* _message, Message::MessageType _typeOfMessage) override;
};