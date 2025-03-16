#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Entity* parent, Sprite* sprite)
: Component(parent), Image(sprite) {}


SpriteRenderer::~SpriteRenderer(){}

int SpriteRenderer::GetBitmask()
{
    return BITMASK;
}
