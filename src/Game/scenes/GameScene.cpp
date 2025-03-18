#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/ui/Image.h"

#include "scripts/PlayerMovement.h"


void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, -500.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>(player);
    ObjectFactory::CreateComponent<Camera>(camera);

    Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);

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