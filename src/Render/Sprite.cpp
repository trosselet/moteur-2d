﻿#include "Sprite.h"

#include "Texture.h"

Sprite::Sprite(Texture* sprite) : mSprite(new sf::Sprite(*sprite->GetTexture()))
{
}

Sprite::Sprite(sf::Sprite* sprite) : mSprite(sprite) {}

sf::Sprite* Sprite::GetSprite()
{
    return mSprite;
}

void Sprite::SetPosition(sf::Vector2f& position)
{
    mSprite->setPosition(position);
}

void Sprite::SetAlpha(uint8_t alpha)
{
    mSprite->setColor(sf::Color(255, 255, 255, alpha));
}

Sprite* Sprite::Cut(int x, int y, int width, int height)
{
    sf::Sprite* part = new sf::Sprite(*mSprite);
    part->setTextureRect(sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(width, height)));
    part->scale(sf::Vector2f(1.0f, 1.0f));
    return new Sprite(part);
}