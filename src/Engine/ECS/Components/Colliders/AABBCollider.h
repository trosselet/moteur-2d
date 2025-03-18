﻿#pragma once
#include "ECS/Components/Collider2D.h"

class AABBCollider : public Collider2D
{
public:
    AABBCollider(Entity* entity, float xMin, float yMin, float xMax, float yMax);
    float GetMaxX() const { return mXMax; }
    float GetMaxY() const { return mYMax; }
    float GetMinX() const { return mXMin; }
    float GetMinY() const { return mYMin; }
protected:
    float mXMin;
    float mYMin;
    float mXMax;
    float mYMax;
    
};
