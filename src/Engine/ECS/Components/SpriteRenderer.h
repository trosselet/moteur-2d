#pragma once

#include "Component.h"
#include "Render/Sprite.h"

class SpriteRenderer : public Component
{

public:
    static constexpr int BITMASK = 1 << 2;
    
    SpriteRenderer(Entity* parent, Sprite* sprite);
    ~SpriteRenderer() override;
    int GetBitmask() override;

    Sprite* Image;
};
