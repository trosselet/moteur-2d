#pragma once
#include "scripts/Script.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement() = default;
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

private:
    sf::Vector2f movement;
};
