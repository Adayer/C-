#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#define LITE_GFX_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include "../project/WordRender.h"

#include "../project/vec2.h"
#include "../project/CTime.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>


using namespace std;
GLFWwindow* mainWindow;

void SpawnHelloWorld(std::vector<WordRender*>* _fonts);
void UpdateHelloWorld(std::vector<WordRender*>* _fonts, double deltaTime);
void DestroyHelloWorld(std::vector<WordRender*>* _fonts);
void DestroyEmptyHelloWorld(std::vector<WordRender*>* _fonts, int numToDestroy);


#define SCR_WIDTH 800
#define SCR_HEIGHT 600

Font* orange = nullptr;
Font* slap = nullptr;

int main() {
    if (!glfwInit()) {
        return 0;
    }

    srand(time(0));


    mainWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica1", nullptr, nullptr);

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(SCR_WIDTH, SCR_HEIGHT);

    CTime time;
    std::vector<WordRender*> fontList;
    orange = new Font();
    orange->LoadFont("data/Orange.ttf");
    slap = new Font();
    slap->LoadFont("data/SFSlapstickComic.ttf");
    

#pragma region FontInitCommented
    ////Fonts Init
    //const int textSize = 1024;
    //FILE* font1 = nullptr;
    //const char* font1Route = "data/SFSlapstickComic.ttf";
    //fopen_s(&font1, font1Route, "rb");

    //if (!font1)
    //{
    //    assert(0);
    //}
    //fseek(font1, 0, SEEK_END);
    //int tellNum = ftell(font1);
    //fseek(font1, 0, SEEK_SET);

    //char* bufferFont1 = new char[tellNum];

    //size_t num = fread(bufferFont1, sizeof(char), tellNum, font1);
    //int cosa2 = fclose(font1);

    //unsigned char* bufferPixels1 = new unsigned char[textSize * textSize];
    //unsigned char* bufferRGB1 = new unsigned char[textSize * textSize * 4];
    //stbtt_bakedchar* bakedCharsData = new stbtt_bakedchar[256];

    //for (unsigned int i = 0; i < textSize * textSize; ++i)
    //{
    //    bufferPixels1[i] = 0;
    //}
    //unsigned char* data = reinterpret_cast<unsigned char*>(bufferFont1);

    //int cosa = stbtt_BakeFontBitmap(data, 0, 64, bufferPixels1, textSize, textSize, 0, 255, bakedCharsData);

    //for (unsigned int i = 0; i < textSize * textSize * 4; ++i)
    //{
    //    bufferRGB1[i] = 255;
    //}

    //for (long unsigned int i = 0; i < textSize * textSize; ++i)
    //{
    //    bufferRGB1[i * 4 + 3] = bufferPixels1[i];
    //}

    //delete[] bufferPixels1;
    //delete[] bufferFont1;
    //int x = textSize;
    //int y = textSize;
    //int* pX = &x;
    //int* pY = &y;

    //ltex_t* text_font1 = ltex_alloc(*pX, *pY, 1);
    //ltex_setpixels(text_font1, bufferRGB1);

    //float fX = 0;
    //float fY = 0;
    //float* pfX = &fX;
    //float* pfY = &fY;

    //stbtt_aligned_quad* infoQuad = new stbtt_aligned_quad();
#pragma endregion



    float elapsedTime = 0.f;

    while (glfwWindowShouldClose(mainWindow) == 0)
    {
        lgfx_clearcolorbuffer(0, 0, 0);

        time.UpdateDeltaTime();

        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(mainWindow, 1);
        }
       
        elapsedTime -= time.DeltaTime();
        if (elapsedTime <= 0)
        {
            elapsedTime = rand() % 2 / 4.f;
            SpawnHelloWorld(&fontList);
        }
        lgfx_setblend(BLEND_ALPHA);
        UpdateHelloWorld(&fontList, time.DeltaTime());
        DestroyHelloWorld(&fontList);


#pragma region FontPaintCommented
        ////Escape to close Window
        //lgfx_setcolor(0, 1, 0, 1);
        //stbtt_GetBakedQuad(bakedCharsData, textSize, textSize, 33, pfX, pfY, infoQuad, true);
        //ltex_drawrotsized(text_font1,
        //    50, 50,
        //    0.f,
        //    0.f, 0.f,
        //    200.f, 200.f, infoQuad->s0, infoQuad->t0,
        //    infoQuad->s1, infoQuad->t1);
#pragma endregion
 
        glfwSwapBuffers(mainWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

const int textSize = 1024;



void SpawnHelloWorld(std::vector<WordRender*>* _fonts)
{
    int randVal = rand() % 100;
    if (randVal % 2)
    {
        (*_fonts).push_back(new WordRender(orange));
    }
    else
    {
        (*_fonts).push_back(new WordRender(slap));
    }
}

void UpdateHelloWorld(std::vector<WordRender*>* _fonts, double deltaTime)
{
    std::vector<WordRender*>::iterator iter;
    for (iter = (*_fonts).begin(); iter != (*_fonts).end(); ++iter)
    {
        if ((*iter)->GetWordPos() >= SCR_WIDTH)
        {
            delete* iter;
            *iter = nullptr;
        }
        else
        {
            (*iter)->DrawHolaMundo(deltaTime);
        }
    }
}

void DestroyHelloWorld(std::vector<WordRender*>* _fonts)
{
    int numEntitiesToDelete = 0;
    std::vector<WordRender*>::iterator iter;
    for (iter = (*_fonts).begin(); iter != (*_fonts).end(); ++iter)
    {
        if (!(*iter))
        {
            numEntitiesToDelete++;
        }
    }
    if (numEntitiesToDelete)
    {
        DestroyEmptyHelloWorld(_fonts, numEntitiesToDelete);
    }
}
void DestroyEmptyHelloWorld(std::vector<WordRender*>* _fonts, int numToDestroy)
{
    std::vector<WordRender*>::iterator iter;
    for (iter = (*_fonts).begin(); iter != (*_fonts).end(); ++iter)
    {
        if (!(*iter))
        {
            (*_fonts).erase(iter);
            --numToDestroy;
            break;
        }
    }
    if (numToDestroy)
    {
        DestroyEmptyHelloWorld(_fonts, numToDestroy);
    }
}