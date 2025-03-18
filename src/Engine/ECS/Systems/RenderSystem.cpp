#include "pch.h"
#include "RenderSystem.h"

#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/Collider2D.h"
#include "Render/RenderWindow.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

void RenderSystem::Render(ECS* globalEC)
{
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (globalEC->HasComponent<SpriteRenderer>(i))
        {
            SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(i);
            renderer->Image->SetPosition(renderer->GetEntity()->GetTransform()->position);
            window->Draw(renderer->Image);
        }

        if(globalEC->HasComponent<Collider2D>(i))
        {
            Collider2D* coll = globalEC->GetComponent<Collider2D>(i);
            coll->GetShape()->setOrigin({0.5f,0.5f});
            window->Draw(coll->GetShape());
        }
    }
}