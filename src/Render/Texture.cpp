#include "Texture.h"

#include <iostream>
#include <ostream>

#include "Engine/Utils/Debug.h"

Texture::Texture(std::string path)
{
    if (loadFromFile("../../res/Textures/" + path))
    {
        Debug::Error("La texture " + path + " was not found.");
    }
}
