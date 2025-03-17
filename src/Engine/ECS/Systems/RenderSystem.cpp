﻿#include "pch.h"
#include "RenderSystem.h"

#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/ui/Image.h"
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
        } else if (globalEC->HasComponent<Image>(i))
        {
            Image* renderer = globalEC->GetComponent<Image>(i);
            renderer->UIImage->SetPosition(renderer->GetEntity()->GetTransform()->position);
            window->Draw(renderer->UIImage);
        }
    }
}