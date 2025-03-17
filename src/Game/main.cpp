#include "pch.h"
#include "main.h"

#include "Engine.h"
#include "Managers/GameManager.h"
#include "scenes/GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));
    
    Engine::CreateRender();
    
    Engine::GetGameManager()->LaunchScene<GameScene>();


#undef CONSOLE_OUTPUT
    return 0;
}
