#include "pch.h"
#include "MusicScript.h"

void MusicScript::OnStart()
{
    if (!music.openFromFile("../../res/Music/musique.mp3"))
    {
        std::cerr << "Error loading musique.mp3" << std::endl;
        return;
    }

    music.play();
    beatClock.restart();

    hitRect.setFillColor(sf::Color::White);
	hitRect.setSize(sf::Vector2f(1920.f, 5.f));
    hitRect.setPosition(sf::Vector2(0.f, 800.f));

}

void MusicScript::OnFixedUpdate()
{
}

void MusicScript::OnUpdate()
{
    float currentTime = beatClock.getElapsedTime().asSeconds();

    float beatNumber = currentTime / SECONDS_PER_BEAT;
    int closestBeat = static_cast<int>(beatNumber + 0.5f);
    float expectedTime = closestBeat * SECONDS_PER_BEAT;

    float realFallSpeed = FALL_SPEED * AR;

    static sf::Clock frameClock;
    float deltaTime = frameClock.restart().asSeconds();

    if (static_cast<int>(beatNumber) > static_cast<int>((currentTime - deltaTime) / SECONDS_PER_BEAT))
    {
        BeatCircle newCircle;
        newCircle.shape = sf::CircleShape(30.f);
        newCircle.shape.setFillColor(sf::Color::White);
        newCircle.shape.setPosition(sf::Vector2f(900.f, 0.f));
        newCircle.beatTime = expectedTime;

        fallingCircles.push_back(newCircle);
    }

    for (auto& beatCircle : fallingCircles)
    {
        beatCircle.shape.move(sf::Vector2f(0.f, realFallSpeed * deltaTime));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        for (auto it = fallingCircles.begin(); it != fallingCircles.end();)
        {
            sf::CircleShape& circle = it->shape;
            float spawnTime = it->beatTime;

            float circleY = circle.getPosition().y;
            float hitY = hitRect.getPosition().y;

            float realFallSpeed = FALL_SPEED * AR;
            float hitExpectedTime = spawnTime + (hitY / realFallSpeed);

            if (std::abs(circleY - hitY) <= 100.0f )
            {
                float timeDifference = std::abs(currentTime - hitExpectedTime);
                if (timeDifference <= TIMING_WINDOW)
                {
                    CONSOLE_OUTPUT(L"Perfect hit!" << std::endl);
                }
                else
                {
                    CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
                }

                CONSOLE_OUTPUT(circleY << " " << hitY << std::endl);
                it = fallingCircles.erase(it);
            }
            else
            {   
                it++;
            }
        }
    }

}

void MusicScript::OnDisable()
{
    music.stop();
}

void MusicScript::OnRender(RenderWindow* window)
{
    window->draw(hitRect);
    for (const auto& beatCircle : fallingCircles)
    {
        window->draw(beatCircle.shape);
    }
}