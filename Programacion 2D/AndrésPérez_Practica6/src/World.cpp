#include "World.h"
#include <iterator>

#define BACKGROUND_LIST(_ACTION)\
_ACTION(back0, 0)\
_ACTION(back1, 1)\
_ACTION(back2, 2)\
_ACTION(back3, 3)

#define CHECK_AND_CREATE(back, index)\
if (back)\
{\
    m_backgrounds[index] = new Background(back);\
}

#define ADD_BACKGROUNDS BACKGROUND_LIST(CHECK_AND_CREATE)


World::World(float clearRed, float clearGreen, float clearBlue,
    const ltex_t* back0,
    const ltex_t* back1,
    const ltex_t* back2,
    const ltex_t* back3) :
    m_clearRed(clearRed),
    m_clearGreen(clearGreen),
    m_clearBlue(clearBlue)
{
    ADD_BACKGROUNDS
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
    for (unsigned int i = 0; i < 4; ++i)
    {
        m_backgrounds[i]->Update(_deltaTime);
    }

    for (size_t i = 0; i < m_spritesToRender.size(); ++i)
    {
        m_spritesToRender[i]->Update(_deltaTime);
    }
}

void World::Draw(const vec2& _screenSize)
{

    lgfx_clearcolorbuffer(m_clearRed, m_clearGreen, m_clearBlue);

    for (unsigned int i = 0; i < 4; ++i)
    {
        m_backgrounds[i]->Draw(_screenSize);
    }

    for (size_t i = 0; i < m_spritesToRender.size(); ++i)
    {
        m_spritesToRender[i]->Draw();
    }
}