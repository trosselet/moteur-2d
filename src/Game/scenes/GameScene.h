#pragma once
#include "Managers/Scene.h"

class GameScene : public Scene
{
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override;

};
