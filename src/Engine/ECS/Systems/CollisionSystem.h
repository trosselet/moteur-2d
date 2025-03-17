#pragma once

class ECS;

class CollisionSystem
{
    float mFixedTimestep = 1.0f / 60.0f;
public:
    static CollisionSystem& Get();
    CollisionSystem();
};
