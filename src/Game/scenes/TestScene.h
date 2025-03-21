#pragma once
#include "ECS/Entity.h"
#include "Managers/Scene.h"

class TestScene: public Scene
{

    Entity* player;
private:
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override;

};
