#pragma once
#include "scripts/Script.h"


class EntityStateScript : public IScript
{
public:
	EntityStateScript();
	~EntityStateScript();

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;
    void OnRender(RenderWindow* window) override;

private:
    sf::Text playerStateText = *Resources::instance().DEFAULT_FONT;

};

