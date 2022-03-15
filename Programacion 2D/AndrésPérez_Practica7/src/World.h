#pragma once

#include <glfw3.h>
#include <stb_image.h>
#include <vector>
#include "vector2.h"
#include "Sprite.h"
#include "Background.h"
#include "pugixml/pugixml.hpp"
class CTime;
class World
{
    //VARIABLES
public:
private:
    const float m_clearRed;
    const float m_clearGreen;
    const float m_clearBlue;

    Background* m_backgrounds[1];

    std::vector<CSprite*> m_spritesToRender;
    std::vector<CSprite*> m_spritesToRemove;
    
    vec2 m_cameraPosition;
    vec2 m_mapSize;

    std::vector<CSprite*> m_tTiles;
    CTime* m_time;

    //Player anim
    bool bRunning = false;
    CSprite* idleSprite;
    CSprite* runSprite;


    //FUNCTIONS
public:
    World(CTime& _time, float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
        const ltex_t* back0 = nullptr);


    float GetClearRed() const { return m_clearRed; }
    float GetClearGreen() const { return m_clearGreen; }
    float GetClearBlue() const { return m_clearBlue; }

    const ltex_t* GetBackground(size_t layer) const
    {
        return m_backgrounds[layer]->GetTexture();
    }

    float GetScrollRatio(size_t layer) const { return m_backgrounds[layer]->GetScrollRatio(); }
    void SetScrollRatio(size_t layer, float ratio) { m_backgrounds[layer]->SetScrollRatio(ratio); }

    const vec2& GetScrollSpeed(size_t layer) const { return m_backgrounds[layer]->GetScrollSpeed(); }
    void SetScrollSpeed(size_t layer, const vec2& speed) { m_backgrounds[layer]->SetScrollSpeed(speed); }

    const vec2& GetCameraPosition() const { return m_cameraPosition; }
    void SetCameraPosition(const vec2& pos) 
    {
        m_cameraPosition = pos; 
        if (m_cameraPosition.x < 400)
        {
            m_cameraPosition.x = 400; 
        }
        else if (m_cameraPosition.x + 400 > m_backgrounds[0]->GetTexture()->width)
        {
            m_cameraPosition.x = (m_backgrounds[0]->GetTexture()->width - 400);
        }
        m_cameraPosition.y = 0;
    }

    void AddSprite(CSprite& sprite) { m_spritesToRender.push_back(&sprite); }
    void RemoveSprite(CSprite& sprite) { m_spritesToRemove.push_back(&sprite); }
    void DestroyTickedSprites();
    void DestroySprite();


    void Update(float deltaTime);
    void Draw(const vec2& screenSize);

    bool loadMap(const char* filename, uint16_t firstColId);
    vec2 getMapSize() const;
    inline std::string extractPath(const std::string& filename);
    bool movePlayer(const vec2& amount);

    void SetPlayerSprites(CSprite* _idleSprite, CSprite* _runSprite)
    {
        idleSprite = _idleSprite;
        runSprite = _runSprite;
    }
private:
    bool moveSprite(CSprite& sprite, const vec2& amount);

};