
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "vector2.h"
#include "Time.h"
#include <stb_image.h>
#include <string>
#include "stb_truetype.h"

#pragma region MarcosPractica 2
//
//#define TEXTURE_LIST(_ACTION)\
//_ACTION(Fire, png)\
//_ACTION(Grille,png)\
//_ACTION(Light, png)\
//_ACTION(Wall, jpg)
//
//#define LOAD_TEXTURE(_FILE_NAME, _TYPE)\
//    int x##_FILE_NAME = 0;\
//    int y##_FILE_NAME = 0;\
//    int* xText##_FILE_NAME = &x##_FILE_NAME;\
//    int* yText##_FILE_NAME = &y##_FILE_NAME;\
//    \
//    std::string str##_FILE_NAME = "data/";\
//    str##_FILE_NAME.append(#_FILE_NAME);\
//    str##_FILE_NAME.append(".");\
//    str##_FILE_NAME.append(#_TYPE);\
//    \
//    unsigned char* textChar##_FILE_NAME = stbi_load(str##_FILE_NAME.c_str(), xText##_FILE_NAME, yText##_FILE_NAME, nullptr, 4);\
//    ltex_t* text##_FILE_NAME = ltex_alloc(*xText##_FILE_NAME, *yText##_FILE_NAME, 1);\
//    ltex_setpixels(text##_FILE_NAME, textChar##_FILE_NAME);\
//    stbi_image_free(textChar##_FILE_NAME);
//
//#define GENERATE_TEXTURES TEXTURE_LIST(LOAD_TEXTURE) 
//
//#define UNLOAD_TEXTURES TEXTURE_LIST(FREE_TEXTURE_ACTION)
//#define FREE_TEXTURE_ACTION(_FILE_NAME, _TYPE) ltex_free(text##_FILE_NAME);

#pragma endregion

using namespace std;

FILE* font1 = nullptr;

unsigned char bufferFont1[2000];
unsigned char bufferPixels1[2000];

unsigned char bufferRGB1[10] = {"9"}; //1048576

stbtt_bakedchar bakedCharsData[2000];

int main() {

    if (!glfwInit()) {
        return 0;
    }

    int screenWidth = 800;
    int screenHeight = 800;

    GLFWwindow* mainWindow(glfwCreateWindow(screenWidth, screenHeight, "Practica 1", nullptr, nullptr));

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(screenWidth, screenHeight);

    CTime time;

    //Fonts Init
    

    const char* font1Route = "data/Orange.ttf";
    fopen_s(&font1, font1Route, "r");

    if (!font1)
    {
        assert(0);
    }

    size_t num = fread(bufferFont1, sizeof(char), 2000, font1);
    

    int x = 2048;
    int y = 2048;
    int* pX = &x;
    int* pY = &y;

    stbtt_BakeFontBitmap(bufferFont1, 0, 20, bufferPixels1, 512, 512, 0, 255, bakedCharsData);

    
    for (size_t i = 0; i < 2000; ++i)
    {
        bufferRGB1[i * 4 + 3] = bufferPixels1[i];
    }
   
    ltex_t* text_font1 = ltex_alloc(*pX, *pY, 1);
    ltex_setpixels(text_font1, bufferRGB1);

    float fX = 0;
    float fY = 0;
    float* pfX = &fX;
    float* pfY = &fY;

    stbtt_aligned_quad* infoQuad = new stbtt_aligned_quad();

    while (glfwWindowShouldClose(mainWindow) == 0)
    {
        time.UpdateDeltaTime();

        glfwPollEvents();

        //Escape to close Window
        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(mainWindow, 1);
        }

        //stbtt_GetBakedQuad(bakedCharsData, 20, 20, 41, pfX, pfY, infoQuad, true);
        //ltex_drawrotsized(text_font1, infoQuad->x0, infoQuad->y0, 0.f, 0.f, 0.f, 60.f, 60.f, infoQuad->s0, infoQuad->t0, infoQuad->s1, infoQuad->t1);

        lgfx_clearcolorbuffer(255, 0, 0);
        ltex_drawrotsized(text_font1, infoQuad->x0, infoQuad->y0, 0.f, 0.f, 0.f, 512.f, 512.f, 0, 0, 1, 1);
        
        glfwSwapBuffers(mainWindow);
    }

    glfwTerminate();
    return 0;
}


