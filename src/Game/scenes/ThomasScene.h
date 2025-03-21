#pragma once
#include "Managers/Scene.h"
#include "ECS/Entity.h"
#include <SFML/Graphics/Text.hpp>

class ThomasScene : public Scene
{
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override;
};
