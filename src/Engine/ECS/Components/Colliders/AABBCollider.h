#pragma once
#include "ECS/Components/Collider2D.h"

class AABBCollider : public Collider2D
{
public:
    AABBCollider(Entity* entity, float xMin, float yMin, float width, float height);
    float GetWidth() const { return mWidth; }
    float GetHeight() const { return mHeight; }
    float GetMinX() const { return mXMin; }
    float GetMinY() const { return mYMin; }
protected:
    float mXMin;
    float mYMin;
    float mWidth;
    float mHeight;
    
};
