#include "WordRender.h"
#include <random>
WordRender::WordRender(Font* _font) :
	font(_font),
	infoQuad(new stbtt_aligned_quad()),
	wordInitPosX(0),
	wordInitPosY(rand() % 500 + 50),
	speed(rand() % 200 + 50),
	r(rand() % 255 / 255.f),
	g(rand() % 255 / 255.f),
	b(rand() % 255 / 255.f)
{

}

void WordRender::DrawHolaMundo(float deltaTime)
{
    wordInitPosX = wordInitPosX  + speed * deltaTime;
    
    lgfx_setcolor(r, g, b, 1);
    float fX = wordInitPosX;
    float fY = wordInitPosY;
    float* pfX = &fX;
    float* pfY = &fY;


    int letterIndex[11] = { 72, 111, 108, 97, 0, 109, 117, 110, 100, 111, 33 };
    for (unsigned int i = 0; i < 11; ++i)//Hola Mundo!12; 
    {
        stbtt_GetBakedQuad(font->GetBakedCharData(), 
            font->textSize, font->textSize,
            letterIndex[i], 
            pfX, pfY, 
            infoQuad, true);
        ltex_drawrotsized(font->GetText(),
            fX, fY + 50,
            0.f,
            1.f, 0.5f,
            infoQuad->x1 - infoQuad->x0, infoQuad->y1 - infoQuad->y0,
            infoQuad->s0, infoQuad->t0,
            infoQuad->s1, infoQuad->t1);
    }
}