#pragma once
#include "scripts/Script.h"
#include <set>

struct Tile
{
    Sprite* texture;
    sf::Vector2f position;
};

class TilemapEditor : public IScript
{
    TRANSFORM* mTransform;
    sf::Vector2f movement;
    
    sf::Vector2i mousePosition;
    
    sf::RectangleShape mSelector;
    sf::VertexArray mGridVertices;
    std::vector<Tile> mTiles;
    std::set<int> mUsedTile;

    sf::Vector2i mCurrentCase;
    sf::Vector2i mOffset;

    int mapSize = 5000;
    int halfMapSize = mapSize/2;
    int tileSize = 50;
    int tilePerRow = mapSize/tileSize;
    int totalTile = tilePerRow*tilePerRow;

public:
    TilemapEditor();
    void OnStart() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnRender(RenderWindow* window) override;
};
