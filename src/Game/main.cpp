#include "pch.h"
#include "main.h"

#include "Engine.h"
#include "Managers/GameManager.h"
#include "scenes/GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));
    
    Engine::SetRenderWindow(hInstance);
    
    Engine::GetGameManager()->LaunchScene<GameScene>();
    
    return 0;
}
