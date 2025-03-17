#pragma once
#include "ECS/Components/Collider2D.h"

class AABBCollider : Collider2D
{
public:
    AABBCollider(int width, int height);
    
protected:
    int mWidth;
    int mHeight;
    
};
