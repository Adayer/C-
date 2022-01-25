#pragma once

#include <litegfx.h>
#include <glfw3.h>
#include "stb_truetype.h"

class Font
{
private:
	ltex_t* text_font;
	stbtt_bakedchar* bakedCharsData;

public:
	const int textSize = 1024;
	void Font::LoadFont(const char* fontFileRoute);
	~Font()
	{
		delete bakedCharsData;
	}
	ltex_t* GetText() const { return text_font; }
	stbtt_bakedchar* GetBakedCharData() const { return bakedCharsData; }

};