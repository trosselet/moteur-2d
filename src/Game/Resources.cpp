#include "pch.h"
#include "Resources.h"

#include "Render/Sprite.h"
#include "Render/Texture.h"

Resources::~Resources()
{
}

void Resources::CreateShaders()
{
}

void Resources::CreateParticles()
{
}

void Resources::CreateTextures()
{
    Texture* tex = new Texture("test.png");
    TEXTURE = new Sprite(tex);
}

void Resources::CreateMaterials()
{
}
