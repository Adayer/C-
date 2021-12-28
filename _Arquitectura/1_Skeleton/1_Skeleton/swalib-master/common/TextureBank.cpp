#include "TextureBank.h"
#include "core.h"

TextureBank* TextureBank::instance = nullptr;

GLuint* TextureBank::GetTexture(const char* _fileName)
{
	std::map<const char*, GLuint>::iterator it;

	//Returns pointer to texture if already loaded
	for (it = m_textureMap.begin(); it != m_textureMap.end(); ++it)
	{
		if (!strcmp(_fileName,it->first))
		{
			return &(it->second);
		}
	}

	//If not loaded loads it and adds it to the map
	GLuint newText = CORE_LoadPNG(_fileName, true);
	m_textureMap.insert(std::pair<const char*, GLuint>(_fileName, newText));
	//Returns newly loaded texture
	return &(m_textureMap.find(_fileName)->second);
}