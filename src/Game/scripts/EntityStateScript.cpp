#include "pch.h"
#include "EntityStateScript.h"
#include "Transform.h"

EntityStateScript::EntityStateScript()
{
}

EntityStateScript::~EntityStateScript()
{
}

void EntityStateScript::OnStart()
{
    playerStateText.setString("BPM");
    playerStateText.setCharacterSize(12);
    playerStateText.setFillColor(sf::Color::White);
}

void EntityStateScript::OnFixedUpdate()
{
}

void EntityStateScript::OnUpdate()
{
    playerStateText.setPosition(-owner->GetTransform()->position);
}

void EntityStateScript::OnDisable()
{
}

void EntityStateScript::OnRender(RenderWindow* window)
{
    window->draw(playerStateText);
}
