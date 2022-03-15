#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION

#include "World.h"
#include "main.h"
#include <iostream>
#include "Time.h"
#include <string>
#include "Sprite.h"
#include <vector>
#include "Player.h"

#define TEXTURE_LIST(_ACTION)\
_ACTION(Clouds, png)\
_ACTION(Run, png)\
_ACTION(Idle, png)

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
constexpr float ROTATION_SPEED = 128.f;
constexpr float MAX_ROTATION = 15.f;

void UpdateSprite(CSprite& _sprite, float _deltaTime);

int main() {

    if (!glfwInit()) {
        return 0;
    }

    int screenWidth = 1024;
    int screenHeight = 1024;

    GLFWwindow* mainWindow(glfwCreateWindow(screenWidth, screenHeight, "Practica 1", nullptr, nullptr));

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(screenWidth, screenHeight);


    //La variable de acceso a ltex_t* se llama text + Indice (text1, text2,...), la otra es textChar + Indice
    GENERATE_TEXTURES



    CTime time;

    World* world = new World(time, 0.f, 0.5f, 0.75f, textClouds);

    Player* pPlayerData = new Player();
    CSprite* playerSprite = new CSprite(textRun, COLLISION_RECT, 6, 1, true);
    playerSprite->SetColor(1.f, 1.f, 1.f);
    playerSprite->SetPivot(vec2(0.5f, 0.5f));
    playerSprite->SetScale(vec2(1.f, 1.f));
    playerSprite->SetBlendMode(BLEND_ALPHA);
    playerSprite->SetPosition(vec2(664.f, 300.f));
    playerSprite->SetUserData(pPlayerData);
    playerSprite->SetFPS(8.f);
    playerSprite->SetCurrentFrame(1);
    playerSprite->SetForcedSize(vec2(32.f, 32.f));
    playerSprite->SetIsActive(false);
    world->AddSprite(*playerSprite);

    CSprite* playerIdleSprite = new CSprite(textIdle, COLLISION_RECT);
    playerIdleSprite->SetColor(1.f, 1.f, 1.f);
    playerIdleSprite->SetPivot(vec2(0.5f, 0.5f));
    playerIdleSprite->SetScale(vec2(1.f, 1.f));
    playerIdleSprite->SetBlendMode(BLEND_ALPHA);
    playerIdleSprite->SetPosition(vec2(664.f, 300.f));
    playerIdleSprite->SetUserData(pPlayerData);
    playerIdleSprite->SetForcedSize(vec2(32.f, 32.f));
    world->AddSprite(*playerIdleSprite);
   
    world->SetPlayerSprites(playerIdleSprite, playerSprite);

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
        float xInput = 0.f;
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT))
        {
            xInput = 1.f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_LEFT))
        {
            xInput = -1.f;
        }
        if (glfwGetKey(mainWindow, GLFW_KEY_SPACE))
        {
            pPlayerData->SetCurrentYSpeed(pPlayerData->JUMP_VELOCITY);
        }
        //Mouse position
        glfwGetCursorPos(mainWindow, &xPos, &yPos);
        mousePos.x = xPos;
        mousePos.y = yPos;
        
        //Update Logic
        //world->SetCameraPosition(vec2(0.f, 0.f));
        world->Update(time.DeltaTime());
        world->movePlayer(vec2(xInput, 0.f));
        
        //Render
        world->Draw(vec2(screenWidth, screenHeight));
        //Render static sprites
        
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