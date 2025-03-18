#include "pch.h"
#include "PlayerMovement.h"

#include "ObjectFactory.h"
#include "Resources.h"
#include "Transform.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "Managers/InputManager.h"

void PlayerMovement::OnStart()
{
}

void PlayerMovement::OnFixedUpdate()
{
   
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    std::cout << "Collision Enter" << std::endl;
}

// TODO Passer de Engine::GetInputManager() a IsKeyJustPressed(KEY_F11)
void PlayerMovement::OnUpdate()
{
    if (Engine::GetInputManager()->IsKeyPressed(KEY_A))
    {
        Entity* entity = ObjectFactory::CreateEntity<Entity>();
        entity->GetTransform()->position = sf::Vector2f(100.0f, 150.0f);
        ObjectFactory::CreateComponent<SpriteRenderer>(entity, Resources::instance().DEFAULT_SPRITE);
        ObjectFactory::CreateComponent<RigidBody2D>(entity);
    }

    if(Engine::GetInputManager()->IsKeyPressed(KEY_S))
    {
        sf::Vector2f newPos = {owner->GetTransform()->position.x, owner->GetTransform()->position.y + 100 * Engine::GetDeltaTime()};
        owner->GetTransform()->SetPosition(newPos);
    }

    if(Engine::GetInputManager()->IsKeyPressed(KEY_Z))
    {
        sf::Vector2f newPos = {owner->GetTransform()->position.x, owner->GetTransform()->position.y - 100 * Engine::GetDeltaTime()};
        owner->GetTransform()->SetPosition(newPos);
    }

    if(Engine::GetInputManager()->IsKeyPressed(KEY_D))
    {
        sf::Vector2f newPos = {owner->GetTransform()->position.x + 100 * Engine::GetDeltaTime(), owner->GetTransform()->position.y};
        owner->GetTransform()->SetPosition(newPos);
    }

    if(Engine::GetInputManager()->IsKeyPressed(KEY_Q))
    {
        sf::Vector2f newPos = {owner->GetTransform()->position.x - 100 * Engine::GetDeltaTime(), owner->GetTransform()->position.y};
        owner->GetTransform()->SetPosition(newPos);
    }
}


void PlayerMovement::OnDisable()
{
    
}
