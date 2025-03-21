#pragma once
#include "scripts/Script.h"
#include "tilemap/TilemapEditor.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement();
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;

private:
    TRANSFORM* mTransform;
    sf::Vector2f movement;
};
