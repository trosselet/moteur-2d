#include "RenderWindow.h"

#include <iostream>

#include "Sprite.h"

void RenderWindow::Create(std::string title, int width, int height)
{
    mWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

sf::RenderWindow* RenderWindow::GetWindow()
{
    return mWindow;
}

void RenderWindow::BeginFrame()
{
    mWindow->clear(sf::Color::Black);
}

void RenderWindow::Draw(Sprite* sprite)
{
    mWindow->draw(*sprite->GetSprite());
}

void RenderWindow::Draw(const sf::Text* text)
{
    mWindow->draw(*text);
}

void RenderWindow::EndFrame()
{
    mWindow->display();
}

int RenderWindow::GetWindowWidth()
{
    return static_cast<int>(mWindow->getSize().x);
}

int RenderWindow::GetWindowHeight()
{
    return static_cast<int>(mWindow->getSize().y);
}