#pragma once
#include "Font.h"
class WordRender
{
private:
	Font* font;
	stbtt_aligned_quad* infoQuad;

	float wordInitPosX = 0;
	float wordInitPosY = 0;
	float speed = 0;

	float r;
	float g;
	float b;
public:
	WordRender(Font* _font);
	~WordRender()
	{
		delete infoQuad;
	}

	void DrawHolaMundo(float deltaTime);
	float GetWordPos() const { return wordInitPosX; }
};