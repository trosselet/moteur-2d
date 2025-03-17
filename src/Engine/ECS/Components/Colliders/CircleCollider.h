#pragma once
#include "ECS/Components/Collider2D.h"

class CircleCollider : Collider2D
{
public:
    
    CircleCollider(int radius);
    float radius;
};
