#include "Font.h"
#include <iostream>

void Font::LoadFont(const char* fontFileRoute)
{
    FILE* fontFile = nullptr;

    fopen_s(&fontFile, fontFileRoute, "rb");

    if (!fontFile)
    {
        return;
    }
    fseek(fontFile, 0, SEEK_END);
    int tellNum = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    char* bufferFont = new char[tellNum];

    size_t num = fread(bufferFont, sizeof(char), tellNum, fontFile);
    int cosa2 = fclose(fontFile);

    unsigned char* bufferPixels = new unsigned char[textSize * textSize];
    unsigned char* bufferRGB = new unsigned char[textSize * textSize * 4];
    bakedCharsData = new stbtt_bakedchar[256];
    for (unsigned int i = 0; i < textSize * textSize; ++i)
    {
        bufferPixels[i] = 0;
    }
    unsigned char* data = reinterpret_cast<unsigned char*>(bufferFont);

    int fontSize = rand() % 64 + 64;

    int cosa = stbtt_BakeFontBitmap(data, 0, fontSize, bufferPixels,
        textSize, textSize, 0, 255, bakedCharsData);

    for (unsigned int i = 0; i < textSize * textSize * 4; ++i)
    {
        bufferRGB[i] = 255;
    }

    for (long unsigned int i = 0; i < textSize * textSize; ++i)
    {
        bufferRGB[i * 4 + 3] = bufferPixels[i];
    }

    int x = textSize;
    int y = textSize;
    int* pX = &x;
    int* pY = &y;

    text_font = ltex_alloc(*pX, *pY, 1);
    ltex_setpixels(text_font, bufferRGB);

    delete[] bufferPixels;
    delete[] bufferFont;
    delete[] bufferRGB;
}
