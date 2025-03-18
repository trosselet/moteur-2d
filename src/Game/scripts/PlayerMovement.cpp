#include "pch.h"
#include "PlayerMovement.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"

void PlayerMovement::OnStart()
{
    mTransform = owner->GetTransform();
}

void PlayerMovement::OnFixedUpdate()
{
    float speed = 2000.0f;
    mTransform->SetPosition(mTransform->position + movement * speed);
    movement = sf::Vector2f(0, 0);
}

void PlayerMovement::OnUpdate()
{
    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += mTransform->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= mTransform->right * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += mTransform->up * Engine::GetDeltaTime();
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= mTransform->up * Engine::GetDeltaTime();
    }
}

void PlayerMovement::OnDisable()
{
    
}
