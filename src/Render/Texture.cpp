#include "Texture.h"

#include <iostream>
#include <ostream>

Texture::Texture(std::string path): mTexture(new sf::Texture)
{
    if (mTexture->loadFromFile("../../res/Textures/" + path))
    {
        std::cout << "Successfully loaded " << path << "\n";
    }
}

sf::Texture* Texture::GetTexture()
{
    return mTexture;
}
