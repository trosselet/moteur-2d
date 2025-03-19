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
        float spawnTime;
    };

    struct NoteData
    {
        int x;
        int y;
        float time;
    };

public:
    MusicScript() = default;

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void OnRender(RenderWindow* window) override;
    void LoadNotesFromFile(const std::string& filename);

private:
    float BPM = 260.f;
    float SECONDS_PER_BEAT = 60.0f / BPM;
    const float TIMING_WINDOW = 0.065f;
    const float FALL_SPEED = 100.0f;
	const float AR = 8.0f;
    bool musicStarted;
    bool isFirstKeyDown = false;
    bool isSecondKeyDown = false;
    float firstNote;

    sf::Vector2f movement;
    sf::Clock beatClock;
	sf::Music music;
    std::vector<BeatCircle> fallingCircles;
    std::vector<NoteData> noteDataList;
    sf::RectangleShape hitRect;
    sf::RenderWindow* window = nullptr;
};