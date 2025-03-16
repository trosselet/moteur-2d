#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Texture;

class Sprite
{
public:
    Sprite(Texture* sprite);
    Sprite(sf::Sprite* sprite);
    ~Sprite() = default;

    sf::Sprite* GetSprite();

    void SetPosition(sf::Vector2f& position);
    void SetAlpha(uint8_t alpha);
    
    Sprite* Cut(int x, int y, int width, int height);

private:
    sf::Sprite* mSprite ;
};
