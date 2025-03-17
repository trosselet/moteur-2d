#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"

#include "scripts/PlayerMovement.h"


void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    Resources::instance().Initialize();
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, 150.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    ObjectFactory::CreateComponent<RigidBody2D>(player);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);

    inventory.OnStart();

    inventory.DisplayInventory();
    inventory.AddItemCount(ItemList::ARMOR, 1);
    inventory.DisplayInventory();
    inventory.AddItemCount(ItemList::HEALTH_POTION, 5);
    inventory.DisplayInventory();
    inventory.AddItemCount(ItemList::SWORD, 4);
    inventory.DisplayInventory();
    inventory.RemoveItemCount(ItemList::ARMOR, 1);
    inventory.RemoveItemCount(ItemList::HEALTH_POTION, 9);
    inventory.DisplayInventory();
    
}

void GameScene::OnUpdate()
{
}