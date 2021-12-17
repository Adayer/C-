#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "vector2d.h"
#include <vector>
#include <map>
#include <string>
#include "SpriteRenderer.h"


enum class RenderLayer
{
	Invalid = -1, 
	Background, 
	Default,
	Foreground, 
	Count
};

class EngineRenderer
{
private:
	//Singleton variables
	static EngineRenderer* instance;
	EngineRenderer() {}
	
	//Lists of sprites to update
	std::vector<SpriteRenderer*> m_tBackgroundSprites;
	std::vector<SpriteRenderer*> m_tDefaultSprites;
	std::vector<SpriteRenderer*> m_tForegroundSprites;

	//Textures Loaded
	std::map<std::string, GLuint> m_textures;

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
	void UpdateRenderer();
	void ExitRenderer();

	void LoadTexture(std::string _name);

	void AddSprite(SpriteRenderer*& _newSprite, RenderLayer _layer)
	{
		switch (_layer)
		{
			case(RenderLayer::Background):
			{
				m_tBackgroundSprites.push_back(_newSprite);
				break;
			}
			case(RenderLayer::Default):
			{
				m_tDefaultSprites.push_back(_newSprite);
				break;
			}
			case(RenderLayer::Foreground):
			{
				m_tForegroundSprites.push_back(_newSprite);
				break;
			}
		}

	}
};
