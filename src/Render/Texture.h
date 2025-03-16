#pragma once

#include <SFML/Graphics/Texture.hpp>

class Texture
{
public:
    Texture(std::string path);
    sf::Texture& GetTexture();
private:
    sf::Texture* mTexture;
};
