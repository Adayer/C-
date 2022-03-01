#include "World.h"
#include <iterator>

#define BACKGROUND_LIST(_ACTION)\
_ACTION(back0, 0, 0.4, 4, 4)\
_ACTION(back1, 1, 0.6, 4, 1)\
_ACTION(back2, 2, 0.8, 4, 1)\
_ACTION(back3, 3, 1, 1, 1)

#define CHECK_AND_CREATE(back, index, ratio, repsX, repsY)\
if (back)\
{\
    m_backgrounds[index] = new Background(back, ratio, repsX, repsY);\
}

#define ADD_BACKGROUNDS BACKGROUND_LIST(CHECK_AND_CREATE)


World::World(float clearRed, float clearGreen, float clearBlue,
    const ltex_t* back0,
    const ltex_t* back1,
    const ltex_t* back2,
    const ltex_t* back3) :
    m_clearRed(clearRed),
    m_clearGreen(clearGreen),
    m_clearBlue(clearBlue),
    m_cameraPosition(0.f, 0.f)
{
    ADD_BACKGROUNDS
    m_backgrounds[0]->SetScrollSpeed(vec2(-16.f, -8.f));
}

void World::DestroyTickedSprites()
{
    if (m_spritesToRemove.size())
    {
        DestroySprite();
    }
}

void World::DestroySprite()
{
    std::vector<CSprite*>::iterator iter = m_spritesToRemove.begin();

    CSprite* buffer = *iter;

    m_spritesToRender.erase(iter);
    m_spritesToRemove.erase(iter);

    delete buffer;

    if (m_spritesToRemove.size())
    {
        DestroySprite();
    }
}

void World::Update(float _deltaTime)
{
    for (size_t i = 0; i < m_spritesToRender.size(); ++i)
    {
        m_spritesToRender[i]->Update(_deltaTime);
    }
    for (unsigned int i = 0; i < 4; ++i)
    {
        m_backgrounds[i]->Update(_deltaTime, m_cameraPosition);
    }
}

void World::Draw(const vec2& _screenSize)
{

    lgfx_clearcolorbuffer(m_clearRed, m_clearGreen, m_clearBlue);

    for (unsigned int i = 0; i < 4; ++i)
    {
        m_backgrounds[i]->Draw(_screenSize, m_cameraPosition);
    }

    lgfx_setorigin(m_cameraPosition.x, m_cameraPosition.y);

    for (size_t i = 0; i < m_spritesToRender.size(); ++i)
    {
        m_spritesToRender[i]->Draw();
    }
}