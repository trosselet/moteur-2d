#pragma once
#include "scripts/Script.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Text.hpp>

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
    MusicScript();

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;

    void OnRender(RenderWindow* window) override;
    void LoadNotesFromFile(const std::string& filename);
	void SetBPM(float bpm) { BPM = bpm; }

	void IncreaseCombo();
	void ResetCombo();
    void ShowCombo(sf::RenderWindow& window);

	void SetupTexts();
    void SetHitAreas();

private:
    float BPM = 1.f;
    float SECONDS_PER_BEAT = 60.0f / BPM;
    const float TIMING_WINDOW = 0.08f;
    const float FALL_SPEED = 100.0f;
	const float AR = 8.0f;
    bool musicStarted;
    bool sKeyPressed = false;
    bool dKeyPressed = false;
    float firstNote;

    sf::Vector2f movement;
    sf::Clock beatClock;
	sf::Music music;
    std::vector<BeatCircle> fallingCircles;
    std::vector<NoteData> noteDataList;
    sf::RectangleShape hitRect;
	sf::CircleShape hitCircle;
    sf::RenderWindow* window = nullptr;

    sf::Text comboText;
    sf::Text maxComboText; 
	sf::Text BPMText;

    int combo = 0;
    int maxCombo = 0;

};