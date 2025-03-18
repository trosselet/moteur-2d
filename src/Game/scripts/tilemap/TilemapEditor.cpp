#include "pch.h"

#include "TilemapEditor.h"
#include "Transform.h"

#include "Resources.h"

TilemapEditor::TilemapEditor() : mSelector({50, 50}), mTiles(nullptr), mOffset({0, 0})
{
}

void TilemapEditor::OnStart()
{
    mTransform = owner->GetTransform();
    mGridVertices = sf::VertexArray(sf::PrimitiveType::Triangles);

    mOffset.x = halfMapSize;
    mOffset.y = halfMapSize;

    mSelector.setFillColor(sf::Color::Red);

    mTiles = new Tile[totalTile];
    for (int x = 0; x < tilePerRow; x++)
    {
        for (int y = 0; y < tilePerRow; y++)
        {
            mTiles[tilePerRow*y+x].texture = nullptr;
            mTiles[tilePerRow*y+x].position = {x, y};
        }
    }

    for (int x = 0; x <= tilePerRow; x++) {
        int tileX = x * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+5, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+5, mapSize), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, mapSize), sf::Color::Red));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+5, mapSize), sf::Color::Red));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+5, 0), sf::Color::Red));

    }
    
    for (int y = 0; y <= tilePerRow; y++) {
        int tileY = y * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+5), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY+5), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+5), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));

    }
}

void TilemapEditor::OnFixedUpdate()
{
    mTransform->SetPosition(mTransform->position + movement);
    movement = sf::Vector2f(0, 0);
}

void TilemapEditor::OnUpdate()
{
    mCurrentCase.x = (mousePosition.x/tileSize) * tileSize + 5;
    mCurrentCase.y= (mousePosition.y/tileSize) * tileSize + 5;
    Debug::Log("X" + std::to_string(mTransform->position.x) + " Y " + std::to_string(mTransform->position.y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        mTiles[tilePerRow * mCurrentCase.y + mCurrentCase.x].texture = Resources::instance().DEFAULT_SPRITE;
    }

    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += mTransform->right * 50.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= mTransform->right * 50.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += mTransform->up * 50.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= mTransform->up * 50.0f;
    }
    
}

void TilemapEditor::OnRender(RenderWindow* window)
{
    
    mousePosition = sf::Mouse::getPosition(*window);
    mSelector.setPosition(sf::Vector2f(mCurrentCase) + mTransform->position);
    
    window->draw(mSelector);
    window->draw(mGridVertices);

    for (int i = 0; i < totalTile; i++)
    {
        if (mTiles[i].texture)
            window->Draw(mTiles[i].texture);
    }
    
}
