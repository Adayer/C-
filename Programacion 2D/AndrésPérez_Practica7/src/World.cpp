#include "World.h"
#include <iterator>
#include <iostream>
#include "Player.h"
#include "Time.h"

#define BACKGROUND_LIST(_ACTION)\
_ACTION(back0, 0, 0.4, 8, 8)

#define CHECK_AND_CREATE(back, index, ratio, repsX, repsY)\
if (back)\
{\
    m_backgrounds[index] = new Background(back, ratio, repsX, repsY);\
}

#define ADD_BACKGROUNDS BACKGROUND_LIST(CHECK_AND_CREATE)


World::World(CTime& _time, float clearRed, float clearGreen, float clearBlue,
    const ltex_t* back0) :
    m_time(&_time),
    m_clearRed(clearRed),
    m_clearGreen(clearGreen),
    m_clearBlue(clearBlue),
    m_cameraPosition(0.f, 0.f)
{
    ADD_BACKGROUNDS
    m_backgrounds[0]->SetScrollSpeed(vec2(-16.f, -8.f));
    loadMap("data/map.tmx", 0);
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
    for (unsigned int i = 0; i < 1; ++i)
    {
        m_backgrounds[i]->Update(_deltaTime, m_cameraPosition);
    }
}

void World::Draw(const vec2& _screenSize)
{

    lgfx_clearcolorbuffer(m_clearRed, m_clearGreen, m_clearBlue);

    for (unsigned int i = 0; i < 1; ++i)
    {
        m_backgrounds[i]->Draw(_screenSize, m_cameraPosition);
    }

    lgfx_setorigin(m_cameraPosition.x, m_cameraPosition.y);

    for (size_t i = 0; i < m_tTiles.size(); ++i)
    {
        m_tTiles[i]->Draw();
    }

    for (size_t i = 0; i < m_spritesToRender.size(); ++i)
    {
        m_spritesToRender[i]->Draw();
    }

}
bool World::loadMap(const char* filename, uint16_t firstColId)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);
    if (result) {
        // Cargado correctamente, podemos analizar su contenido
        pugi::xml_node mapNode = doc.child("map");
        
        pugi::xml_node tilesetNode = mapNode.child("tileset");
        int firstgid = tilesetNode.attribute("firstgid").as_int();
        int tileWidth = tilesetNode.attribute("tilewidth").as_int();
        int tileHeight = tilesetNode.attribute("tileheight").as_int();
        m_mapSize.x = tileWidth;
        m_mapSize.y = tileHeight;
        int tileCount = tilesetNode.attribute("tilecount").as_int();
        int columns = tilesetNode.attribute("columns").as_int();

        pugi::xml_node imageNode = tilesetNode.child("image");
        pugi::char_t fileName[64];
        for (unsigned int i = 0; i < 64; ++i)
        {
            fileName[i] = '\0';
        }
        const pugi::char_t* pName = fileName;
        pName = imageNode.attribute("source").as_string();
        std::string extractedPath(filename);
        std::string sfileName(pName);
        extractedPath = extractPath(extractedPath);
        extractedPath.append(sfileName);
        int imageWidth = imageNode.attribute("width").as_int();
        int imageHeight = imageNode.attribute("height").as_int();

        int xTileMap = 0; 
        int yTileMap = 0;
        int* xTextTileMap = &xTileMap;
        int* yTextTileMap = &yTileMap;
        unsigned char* textCharTileMap = stbi_load(extractedPath.c_str(), xTextTileMap, yTextTileMap, nullptr, 4);
        ltex_t* textTileMap = ltex_alloc(*xTextTileMap, *yTextTileMap, 1);
        ltex_setpixels(textTileMap, textCharTileMap);
        stbi_image_free(textCharTileMap);

        pugi::xml_node layerNode = mapNode.child("layer");
        int layerWidth = layerNode.attribute("width").as_int();
        int layerHeight = layerNode.attribute("height").as_int();

        int index = 0;
        for (pugi::xml_node tileNode = layerNode.child("data").child("tile"); 
            tileNode; 
            tileNode = tileNode.next_sibling("tile"))
        {
            int tileID = tileNode.attribute("gid").as_int();
            if (tileID)
            {
                CSprite* newTile = new CSprite(textTileMap, COLLISION_RECT, columns, (tileCount / columns));
                newTile->SetCurrentFrame(tileID - firstgid);

                int yPos = index;
                yPos /= layerHeight;
                yPos *= tileHeight;
                float pruebas = index / layerHeight * tileHeight;
                newTile->SetPosition(vec2(index % layerWidth * tileWidth, index / layerHeight * tileHeight));
                newTile->SetScale(vec2(1.f, 1.f));
                newTile->SetColor(1.f, 1.f, 1.f);
                newTile->SetBlendMode(BLEND_ALPHA);
                newTile->SetPivot(vec2(0.5f, 0.5f));
                newTile->SetForcedSize(vec2(tileWidth, tileHeight));
                m_tTiles.push_back(newTile);
            }
            ++index;
        }
    }
    else {
        // No se ha podido cargar
        std::cout << result.description() << std::endl;
        return nullptr;
    }

}
vec2 World::getMapSize() const
{
    return m_mapSize;
}
bool World::movePlayer(const vec2& amount)
{
    if (amount.x != 0)
    {
        if (!bRunning)
        {
            bRunning = true;
            runSprite->SetIsActive(true);
            idleSprite->SetIsActive(false);
        }
        moveSprite(*runSprite, amount);
        idleSprite->SetPosition(vec2(runSprite->GetPosition().x, runSprite->GetPosition().y));
        idleSprite->SetScale(vec2(runSprite->GetScale().x, runSprite->GetScale().y));
        return true;
    }
    else
    {
        if (bRunning)
        {
            bRunning = false;
            runSprite->SetIsActive(false);
            idleSprite->SetIsActive(true);
        }
        moveSprite(*idleSprite, amount);

        runSprite->SetPosition(vec2(idleSprite->GetPosition().x, idleSprite->GetPosition().y));
        runSprite->SetScale(vec2(idleSprite->GetScale().x, idleSprite->GetScale().y));
        return true;
    }
}

bool World::moveSprite(CSprite& sprite, const vec2& amount)
{
    Player* pPlayer = static_cast<Player*>(sprite.GetUserData());
    //Move X
    float xPos = sprite.GetPosition().x;
    float bufferXPos = sprite.GetPosition().x;
    float xOffset = amount.x * pPlayer->MAX_HORIZONTAL_VELOCITY;
    xPos += xOffset * m_time->DeltaTime();
    //CheckCollision
    bool collidesIntoSomething = false;
    sprite.SetPosition(vec2(xPos, sprite.GetPosition().y));
    for (unsigned int i = 0; i < m_tTiles.size(); ++i)
    {
        if (sprite.Collides(*m_tTiles[i]))
        {
            collidesIntoSomething = true;
            sprite.SetPosition(vec2(bufferXPos, sprite.GetPosition().y));
            break;
        }
    }
    if (amount.x < 0 && sprite.GetScale().x > 0)
    {
        sprite.SetScale(vec2(-sprite.GetScale().x, sprite.GetScale().y));
    }
    else if(amount.x > 0 && sprite.GetScale().x < 0)
    {
        sprite.SetScale(vec2(-sprite.GetScale().x, sprite.GetScale().y));
    }

    //Move Y
    float yPos = sprite.GetPosition().y;
    float bufferYPos = sprite.GetPosition().y;
    float newSpeedY = pPlayer->GetCurrentYSpeed();
    newSpeedY = newSpeedY + pPlayer->GRAVITY * m_time->DeltaTime();
    pPlayer->SetCurrentYSpeed(newSpeedY);
    yPos = yPos + pPlayer->GetCurrentYSpeed() * m_time->DeltaTime();
    collidesIntoSomething = false;
    sprite.SetPosition(vec2(sprite.GetPosition().x, yPos));
    for (unsigned int i = 0; i < m_tTiles.size(); ++i)
    {
        if (sprite.Collides(*m_tTiles[i]))
        {
            collidesIntoSomething = true;
            pPlayer->SetCurrentYSpeed(0.f);
            sprite.SetPosition(vec2(sprite.GetPosition().x, bufferYPos));
            break;
        }
    }
    

    return true;
}
inline std::string World::extractPath(const std::string& filename)
{
    std::string filenameCopy = filename;
    while (filenameCopy.find("\\") != std::string::npos) {
        filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
    }
    filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));
    if (filenameCopy.size() > 0) filenameCopy += "/";
    return filenameCopy;
}

