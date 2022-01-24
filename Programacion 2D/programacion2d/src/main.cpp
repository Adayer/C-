#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "../project/vec2.h"
#include "../project/CTime.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <string>


using namespace std;
GLFWwindow* mainWindow;

int main() {
    if (!glfwInit()) {
        return 0;
    }

    int screenWidth = 800;
    int screenHeight = 600;
    const int textSize = 1024;

    mainWindow = glfwCreateWindow(screenWidth, screenHeight, "Practica1", nullptr, nullptr);

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(screenWidth, screenHeight);

    CTime time;

    //Fonts Init
    FILE* font1 = nullptr;
    const char* font1Route = "data/SFSlapstickComic.ttf";
    fopen_s(&font1, font1Route, "rb");

    if (!font1)
    {
        assert(0);
    }
    fseek(font1, 0, SEEK_END);
    int tellNum = ftell(font1);
    fseek(font1, 0, SEEK_SET);

    char* bufferFont1 = new char[tellNum];

    size_t num = fread(bufferFont1, sizeof(char), tellNum, font1);
    int cosa2 = fclose(font1);

    unsigned char* bufferPixels1 = new unsigned char[textSize * textSize];
    unsigned char* bufferRGB1 = new unsigned char[textSize * textSize * 4];
    stbtt_bakedchar* bakedCharsData = new stbtt_bakedchar[256];

    for (unsigned int i = 0; i < textSize * textSize; ++i)
    {
        bufferPixels1[i] = 0;
    }
    unsigned char* data = reinterpret_cast<unsigned char*>(bufferFont1);

    int cosa = stbtt_BakeFontBitmap(data, 0, 64, bufferPixels1, textSize, textSize, 0, 255, bakedCharsData);

    for (unsigned int i = 0; i < textSize * textSize * 4; ++i)
    {
        bufferRGB1[i] = 255;
    }

    for (long unsigned int i = 0; i < textSize * textSize; ++i)
    {
        bufferRGB1[i * 4 + 3] = bufferPixels1[i];
    }

    delete[] bufferPixels1;
    delete[] bufferFont1;
    int x = textSize;
    int y = textSize;
    int* pX = &x;
    int* pY = &y;

    ltex_t* text_font1 = ltex_alloc(*pX, *pY, 1);
    ltex_setpixels(text_font1, bufferRGB1);

    float fX = 0;
    float fY = 0;
    float* pfX = &fX;
    float* pfY = &fY;

    stbtt_aligned_quad* infoQuad = new stbtt_aligned_quad();
    
    lgfx_setblend(BLEND_ALPHA);

    while (glfwWindowShouldClose(mainWindow) == 0)
    {
        lgfx_clearcolorbuffer(255, 255, 0);

        time.UpdateDeltaTime();

        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(mainWindow, 1);
        }

        //Escape to close Window
        lgfx_setcolor(0, 1, 0, 1);
        stbtt_GetBakedQuad(bakedCharsData, textSize, textSize,33, pfX, pfY, infoQuad, true);
        ltex_drawrotsized(text_font1, 
            50, 50,
            0.f, 
            0.f, 0.f, 
            200.f, 200.f, infoQuad->s0, infoQuad->t0,
            infoQuad->s1, infoQuad->t1);


        
        //ltex_drawrotsized(text_font1, infoQuad->x0, infoQuad->y0, 0.f, 0.f, 0.f, textSize.f, textSize.f, 0, 0, 1, 1);
        
        glfwSwapBuffers(mainWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
