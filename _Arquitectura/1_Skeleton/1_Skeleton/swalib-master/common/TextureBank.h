#pragma once
#include <map>
#include <string>
#include "stdafx.h"


class TextureBank
{
private:
	std::map<const char*, GLuint> m_textureMap;
	//Singleton variables
	static TextureBank* instance;
	TextureBank() {}
public:
	//Singleton variables
	static TextureBank* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new TextureBank();
		}
		return instance;
	}

	//To assure singleton is not copied or created using a copy
	TextureBank(TextureBank& other) = delete;
	void operator=(const TextureBank&) = delete;

	GLuint* GetTexture(const char* _fileName); //File Location and name ("data/blueBall.png")
};