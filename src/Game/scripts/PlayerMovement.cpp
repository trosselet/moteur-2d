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

// TODO Passer de Engine::GetInputManager() a IsKeyJustPressed(KEY_F11)
void PlayerMovement::OnUpdate()
{
    if (Engine::GetInputManager()->IsKeyPressed(KEY_A))
    {
        Entity* entity = ObjectFactory::CreateEntity<Entity>();
        entity->GetTransform()->position = sf::Vector2f(100.0f, 150.0f);
        ObjectFactory::CreateComponent<SpriteRenderer>(entity, Resources::instance().TEXTURE);
        ObjectFactory::CreateComponent<RigidBody2D>(entity);
        
    }
}

void PlayerMovement::OnDisable()
{
    
}
