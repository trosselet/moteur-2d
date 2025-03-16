#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Sprite.h"

class RenderWindow final
{
public:
    RenderWindow() = default;
    
    void Create(std::string title, int width, int height);
    sf::RenderWindow* GetWindow();

    void BeginFrame();
    void Draw(Sprite* sprite);
    void Draw(const sf::Text* text);
    void EndFrame();
    
    int GetWindowWidth();
    int GetWindowHeight();

private:
    sf::Text text;
    sf::Font mFont;
    sf::RenderWindow* mWindow;
};