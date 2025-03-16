#include "pch.h"
#include "Image.h"

Image::Image(Entity* entity, Sprite* sprite): Component(entity)
{
    UIImage = sprite;
}

int Image::GetBitmask()
{
    return BITMASK;
}
