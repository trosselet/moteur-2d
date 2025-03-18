#include "pch.h"
#include "TestScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"

#include "scripts/PlayerMovement.h"
void TestScene::OnEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Resources::instance().Initialize();
    
    player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(100.0f, 100.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    ObjectFactory::CreateComponent<CircleCollider>(player, 10.0f);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);

    
    Entity* other = ObjectFactory::CreateEntity<Entity>();
    other->GetTransform()->SetPosition(250.0f,250.0f);
    ObjectFactory::CreateComponent<AABBCollider>(other, 0.0f,0.0f,100.0f,100.0f);
    other->GetComponent<AABBCollider>()->SetStatic(true);

    
    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);
    
}

void TestScene::OnUpdate()
{
    // std::cout << player->GetTransform()->position.x << std::endl;
    // std::cout << player->GetTransform()->position.y << std::endl;
}


