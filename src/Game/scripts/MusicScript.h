#pragma once
#include "scripts/Script.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics.hpp>

class RigidBody2D;

class MusicScript : public IScript
{
    struct BeatCircle
    {
        sf::CircleShape shape;
        float beatTime;
    };

public:
    MusicScript() = default;

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void OnRender(RenderWindow* window) override;

private:
    sf::Vector2f movement;

    float BPM = 173.0f;
    float SECONDS_PER_BEAT = 60.0f / BPM;
    const float TIMING_WINDOW = 0.055f;
    const float FALL_SPEED = 100.0f;
	const float AR = 10.0f;
    sf::Clock beatClock;
	sf::Music music;

    std::vector<BeatCircle> fallingCircles;
    sf::RectangleShape hitRect;
    sf::RenderWindow* window = nullptr;
};