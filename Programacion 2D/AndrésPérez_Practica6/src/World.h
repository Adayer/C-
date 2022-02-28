#pragma once
#include <vector>
#include "vector2.h"
#include "Sprite.h"
#include "Background.h"

class World
{
    //VARIABLES
public:
private:
    const float m_clearRed;
    const float m_clearGreen;
    const float m_clearBlue;

    Background* m_backgrounds[4];

    std::vector<CSprite*> m_spritesToRender;
    std::vector<CSprite*> m_spritesToRemove;

    //FUNCTIONS
public:
    World(float clearRed = 0.15f, float clearGreen = 0.15f, float clearBlue = 0.15f,
        const ltex_t* back0 = nullptr,
        const ltex_t* back1 = nullptr,
        const ltex_t* back2 = nullptr,
        const ltex_t* back3 = nullptr);

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

    const vec2& GetCameraPosition() const;
    void SetCameraPosition(const vec2& pos);

    void AddSprite(CSprite& sprite) { m_spritesToRender.push_back(&sprite); }
    void RemoveSprite(CSprite& sprite) { m_spritesToRemove.push_back(&sprite); }
    void DestroyTickedSprites();
    void DestroySprite();


    void Update(float deltaTime);
    void Draw(const vec2& screenSize);
private:

};