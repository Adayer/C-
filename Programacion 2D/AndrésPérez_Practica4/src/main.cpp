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
_ACTION(Bee, png)

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


constexpr float SPEED = 128.f; 
constexpr float ROTATION_SPEED = 32.f;
constexpr float MAX_ROTATION = 15.f;

void UpdateSprite(CSprite& _sprite, float _deltaTime);

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

    //Sprite Initialization
    CSprite* beeSprite = new CSprite(textBee,8,1);
    beeSprite->SetBlendMode(lblend_t::BLEND_ALPHA);
    beeSprite->SetFPS(8.f);
    beeSprite->SetScale(vec2(1.5f, 1.5f));

    beeSprite->SetCallback(&UpdateSprite);
    

    CTime time;
    double xPos(0.);
    double yPos(0.);
    vec2 mousePos(0.f, 0.f);

    vec2 screenCenterLocation(screenHeight / 2.f, screenHeight / 2.f);


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
       
        //Sprite Update
        beeSprite->SetUserData(&mousePos);
        beeSprite->Update(time.DeltaTime());
        beeSprite->Draw();

        glfwSwapBuffers(mainWindow);
    }
    UNLOAD_TEXTURES
    glfwTerminate();
    return 0;
}

void UpdateSprite(CSprite& _sprite, float _deltaTime)
{
    //Update Position
    vec2 currentTargetPos(*(static_cast<vec2*>(_sprite.GetUserData())));
    vec2 currentPos(_sprite.GetPosition());

    vec2 direction(currentTargetPos - currentPos);
    vec2 normalizedDirection(Normalize(direction));

    currentPos = currentPos + normalizedDirection * (SPEED * _deltaTime);
    _sprite.SetPosition(currentPos);

    //Rotate
    if (direction.x > 0.2f)
    {
        float currentRotation = _sprite.GetRotation() + -ROTATION_SPEED * _deltaTime;
        if (currentRotation < -MAX_ROTATION)
        {
            currentRotation = -MAX_ROTATION;
        }
        _sprite.SetRotation(currentRotation);
    }
    else if(direction.x < 0.2f)
    {
        float currentRotation = _sprite.GetRotation() + ROTATION_SPEED * _deltaTime;
        if (currentRotation > MAX_ROTATION)
        {
            currentRotation = MAX_ROTATION;
        }
        _sprite.SetRotation(currentRotation);
    }
    else
    {
        float bufferRotation = _sprite.GetRotation();
        float currentRotation = _sprite.GetRotation() != 0 ? 
            (_sprite.GetRotation() < 0 
                ? _sprite.GetRotation() + ROTATION_SPEED * _deltaTime 
                : _sprite.GetRotation() - ROTATION_SPEED * _deltaTime) 
            : (0);
       
        if (bufferRotation < 0 && currentRotation > 0)
        {
            currentRotation = 0;
        }
        else if (bufferRotation > 0 && currentRotation < 0)
        {
            currentRotation = 0;
        }
        _sprite.SetRotation(currentRotation);
    }
}