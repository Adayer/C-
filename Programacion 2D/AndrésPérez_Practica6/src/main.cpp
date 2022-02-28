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
#include <vector>

#define TEXTURE_LIST(_ACTION)\
_ACTION(Bee, png)\
_ACTION(Ball, png)\
_ACTION(Box, png)\
_ACTION(Circle, png)\
_ACTION(Rect, png)

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


    float scaleChangeSpeed = 0.1f;
    float scaleMax = 1.1f;
    float scaleMin = 0.9f;
    float currentScaleMod = 1.f; 
    bool isIncreasing = false;

    CSprite* mouseSprite = new CSprite(textCircle, CollisionType::COLLISION_CIRCLE);
    mouseSprite->SetColor(1.f, 1.f, 1.f);
    mouseSprite->SetBlendMode(BLEND_ALPHA);
    mouseSprite->SetScale(vec2(1.f, 1.f));
    mouseSprite->SetPivot(vec2(0.5f, 0.5f));
    std::vector<CSprite*> spriteList;
    spriteList.push_back(new CSprite(textBee, CollisionType::COLLISION_PIXELS));
    spriteList.push_back(new CSprite(textBox, CollisionType::COLLISION_RECT));
    spriteList.push_back(new CSprite(textBall, CollisionType::COLLISION_CIRCLE));

    for (unsigned int i = 0; i < 3; ++i)
    {
        spriteList[i]->SetColor(1.f, 1.f, 1.f);
        spriteList[i]->SetBlendMode(BLEND_ALPHA);
        spriteList[i]->SetScale(vec2(1.f, 1.f));
        spriteList[i]->SetPivot(vec2(0.5f, 0.5f));

        switch(i)
        {
        case 0:
        {
            spriteList[i]->SetPosition(vec2(screenHeight / 2.f - 200, screenHeight / 2.f));
            break;
        }
        case 1:
        {
            spriteList[i]->SetPosition(vec2(screenHeight / 2.f , screenHeight / 2.f));
            break;
        }
        case 2:
        {
            spriteList[i]->SetPosition(vec2(screenHeight / 2.f + 200, screenHeight / 2.f));
            break;
        }
        }
       
    }

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

        if(glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT))
        {
            delete mouseSprite;
            mouseSprite = new CSprite(textCircle, CollisionType::COLLISION_CIRCLE);
            mouseSprite->SetColor(1.f, 1.f, 1.f);
            mouseSprite->SetBlendMode(BLEND_ALPHA);
            mouseSprite->SetScale(vec2(1.f, 1.f));
            mouseSprite->SetPivot(vec2(0.5f, 0.5f));
        }
        else if(glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_RIGHT))
        {
            delete mouseSprite;
            mouseSprite = new CSprite(textRect, CollisionType::COLLISION_RECT);
            mouseSprite->SetColor(1.f, 1.f, 1.f);
            mouseSprite->SetBlendMode(BLEND_ALPHA);
            mouseSprite->SetScale(vec2(1.f, 1.f));
            mouseSprite->SetPivot(vec2(0.5f, 0.5f));
        }
        else if(glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_MIDDLE))
        {
            delete mouseSprite;
            mouseSprite = new CSprite(textBee, CollisionType::COLLISION_PIXELS);
            mouseSprite->SetColor(1.f, 1.f, 1.f);
            mouseSprite->SetBlendMode(BLEND_ALPHA);
            mouseSprite->SetScale(vec2(1.f, 1.f));
            mouseSprite->SetPivot(vec2(0.5f, 0.5f));
        }


        //Mouse position
        glfwGetCursorPos(mainWindow, &xPos, &yPos);
        mousePos.x = xPos;
        mousePos.y = yPos;

        //Render static sprites
        lgfx_clearcolorbuffer(0.f, 0.f, 1.f);
        
        if (isIncreasing)
        {
            currentScaleMod = currentScaleMod + (scaleChangeSpeed * time.DeltaTime());
            if (currentScaleMod > scaleMax)
            {
                currentScaleMod = scaleMax;
                isIncreasing = false;
            }
        }
        else
        {
            currentScaleMod = currentScaleMod - (scaleChangeSpeed * time.DeltaTime());
            if (currentScaleMod < scaleMin)
            {
                currentScaleMod = scaleMin;
                isIncreasing = true;
            }
        }
        spriteList[1]->SetScale(vec2(currentScaleMod, currentScaleMod));
        spriteList[2]->SetScale(vec2(currentScaleMod, currentScaleMod));
        for (int i = 0; i < spriteList.size(); ++i)
        {
            spriteList[i]->Update(time.DeltaTime());
        }

        for(int i = 0; i < spriteList.size(); ++i)
        {
            spriteList[i]->Draw();
        }
        
        bool mouseSpriteIsColliding = false;
        for (int i = 0; i < spriteList.size(); ++i)
        {
            if (spriteList[i]->Collides(*mouseSprite))
            {
                mouseSpriteIsColliding = true;
                break;
            }
        }
        
        mouseSprite->SetColor(1.f, 1.f, 1.f);
        if (mouseSpriteIsColliding)
        {
            mouseSprite->SetColor(1.f, 0.f, 0.f);
        }
        mouseSprite->SetPosition(mousePos);
        mouseSprite->Draw();

        
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