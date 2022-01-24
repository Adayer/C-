#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include "main.h"
#include <glfw3.h>
#include <iostream>
#include "vector2.h"
#include "Time.h"
#include <stb_image.h>
#include <string>
#include "Sprite.h"

#define TEXTURE_LIST(_ACTION)\
_ACTION(Fire, png)\
_ACTION(Grille,png)\
_ACTION(Light, png)\
_ACTION(Wall, jpg)

#define LOAD_TEXTURE(_FILE_NAME, _TYPE)\
    int x##_FILE_NAME = 0;\
    int y##_FILE_NAME = 0;\
    int* xText##_FILE_NAME = &x##_FILE_NAME;\
    int* yText##_FILE_NAME = &y##_FILE_NAME;\
    \
    std::string str##_FILE_NAME = "data/";\
    str##_FILE_NAME.append(#_FILE_NAME);\
    str##_FILE_NAME.append(".");\
    str##_FILE_NAME.append(#_TYPE);\
    \
    unsigned char* textChar##_FILE_NAME = stbi_load(str##_FILE_NAME.c_str(), xText##_FILE_NAME, yText##_FILE_NAME, nullptr, 4);\
    ltex_t* text##_FILE_NAME = ltex_alloc(*xText##_FILE_NAME, *yText##_FILE_NAME, 1);\
    ltex_setpixels(text##_FILE_NAME, textChar##_FILE_NAME);\
    stbi_image_free(textChar##_FILE_NAME);

#define GENERATE_TEXTURES TEXTURE_LIST(LOAD_TEXTURE) 

#define UNLOAD_TEXTURES TEXTURE_LIST(FREE_TEXTURE_ACTION)
#define FREE_TEXTURE_ACTION(_FILE_NAME, _TYPE) ltex_free(text##_FILE_NAME);

using namespace std;

int main() {

    if (!glfwInit()) {
        return 0;
    }

    int screenWidth = 800;
    int screenHeight = 800;

    GLFWwindow* mainWindow(glfwCreateWindow(screenWidth, screenHeight, "Practica 1", nullptr, nullptr));

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(screenWidth, screenHeight);


    //La variable de acceso a ltex_t* se llama text + Indice (text1, text2,...), la otra es textChar + Indice
    GENERATE_TEXTURES


        CTime time;
    double xPos(0.);
    double yPos(0.);
    vec2 mousePos(0.f, 0.f);

    vec2 screenCenterLocation(screenHeight / 2.f, screenHeight / 2.f);


    //Variables for light Rotation and Scale change
    float currentLightRotation = 0.f;
    float lightRotationSpeed = 10.f;
    float maxRotation = 10.f;
    bool rotatingRight = true;

    float currentLightScale = 1.f;
    float lightScaleChangeSpeed = 0.5f; 
    float maxScale = 1.2f;
    float minScale = 0.8f;
    bool scalingUp = true;


    while (glfwWindowShouldClose(mainWindow) == 0)
    {
        time.UpdateDeltaTime();

        glfwPollEvents();

        //Escape to close Window
        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(mainWindow, 1);
        }

        //Mouse position
        glfwGetCursorPos(mainWindow, &xPos, &yPos);
        mousePos.x = xPos;
        mousePos.y = yPos;

        //Renderizar cuadro en el centro de la pantalla
        lgfx_clearcolorbuffer(1.f, 1.f, 1.f);

        ////Wall
        lgfx_setblend(lblend_t::BLEND_SOLID);
        float escalaWallTilingX = screenWidth / xWall;
        float escalaWallTilingY = screenHeight / yWall;
        ltex_drawrotsized(textWall, 0, 0, 0, 0, 0, screenWidth, screenHeight, 0, 0, escalaWallTilingY, escalaWallTilingX);



        //Fire

        //Rotation
        if (rotatingRight)
        {
            currentLightRotation += (lightRotationSpeed * time.DeltaTime());
            if (currentLightRotation > maxRotation)
            {
                currentLightRotation = maxRotation;
                rotatingRight = false;
            }
        }
        else
        {
            currentLightRotation -= (lightRotationSpeed * time.DeltaTime());
            if (currentLightRotation < -maxRotation)
            {
                currentLightRotation = -maxRotation;
                rotatingRight = true;
            }
        }

        //Scale
        if (scalingUp)
        {
            currentLightScale += (lightScaleChangeSpeed * time.DeltaTime());
            if (currentLightScale > maxScale)
            {
                currentLightScale = maxScale;
                scalingUp = false;
            }
        }
        else
        {
            currentLightScale -= (lightScaleChangeSpeed * time.DeltaTime());
            if (currentLightScale < minScale)
            {
                currentLightScale = minScale;
                scalingUp = true;
            }
        }

        lgfx_setblend(lblend_t::BLEND_ADD);
        ltex_drawrotsized(textFire, (mousePos.x), (mousePos.y), currentLightRotation, 0.5f, 0.5f, xFire * currentLightScale, yFire * currentLightScale, 0, 0, 1, 1);

        //Grille
        lgfx_setblend(lblend_t::BLEND_ALPHA);
        float escalaGrilleTilingX = screenWidth / xGrille;
        float escalaGrilleTilingY = screenHeight / yGrille;
        ltex_drawrotsized(textGrille, 0, 0, 0, 0, 0, screenWidth, screenHeight, 0, 0, escalaGrilleTilingX, escalaGrilleTilingX);

        //Light
        
        lgfx_setblend(lblend_t::BLEND_MUL);

        ltex_drawrotsized(textLight, mousePos.x - (xLight / 2.f), mousePos.y - (yLight / 2.f), 0, 0, 0, xLight, yLight, 0, 0, 1, 1);



        //Side squares
        lgfx_setblend(lblend_t::BLEND_SOLID);
        lgfx_setcolor(0.f, 0.f, 0.f, 1.f);

        //Right side square
        if (screenWidth - mousePos.x - (xLight / 2.f) > 0)
        {
            lgfx_drawrect(mousePos.x + (xLight / 2.f), mousePos.y - (yLight / 2.f), screenWidth - mousePos.x - (xLight /2.f), yLight);
        }
        //Left side square
        if (mousePos.x > (xLight / 2.f))
        {
            lgfx_drawrect(mousePos.x - (xLight / 2.f), mousePos.y - (yLight / 2.f), -(mousePos.x - (xLight / 2.f)), yLight);
        }
        
        //Bot side square
        if (screenHeight - mousePos.y - (yLight / 2.f) > 0)
        {
            lgfx_drawrect(0.f,mousePos.y + (yLight/2.f), screenWidth, screenHeight - mousePos.y - (yLight / 2.f));
        }
        //Top side square
        if (mousePos.y > (yLight / 2.f))
        {
            lgfx_drawrect(0.f, mousePos.y - (yLight / 2.f),screenWidth, -(mousePos.y - (yLight / 2.f)));
        }
        lgfx_setcolor(1.f, 1.f, 1.f, 1.f);

        glfwSwapBuffers(mainWindow);
    }
    UNLOAD_TEXTURES
    glfwTerminate();
    return 0;
}