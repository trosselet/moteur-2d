#include "pch.h"
#include "MusicScript.h"
#include <fstream>
#include <sstream>

MusicScript::MusicScript() : comboText(*Resources::instance().DEFAULT_FONT), maxComboText(*Resources::instance().DEFAULT_FONT), BPMText(*Resources::instance().DEFAULT_FONT)
{
}

void MusicScript::SetupTexts()
{
	comboText.setCharacterSize(30);
	comboText.setFillColor(sf::Color::White);
	comboText.setPosition(sf::Vector2f(50, 50));
	maxComboText.setCharacterSize(30);
	maxComboText.setFillColor(sf::Color::White);
	maxComboText.setPosition(sf::Vector2f(50, 125));
	BPMText.setString("BPM: " + std::to_string(BPM));
	BPMText.setCharacterSize(30);
	BPMText.setFillColor(sf::Color::White);
	BPMText.setPosition(sf::Vector2f(50, 200));
}

void MusicScript::SetHitAreas()
{
    hitRect.setFillColor(sf::Color::White);
    hitRect.setSize(sf::Vector2f(1920.f, 5.f));
    hitRect.setPosition(sf::Vector2(0.f, 800.f));

    hitCircle.setFillColor(sf::Color::Magenta);
    hitCircle.setRadius(50.f);
    hitCircle.setPosition(sf::Vector2(1920.f / 2 - 2.f, 750.f));
}

void MusicScript::OnStart()
{
    LoadNotesFromFile("../../res/Beatmaps/4.txt");

    if (!music.openFromFile("../../res/Music/4.ogg"))
    {
        CONSOLE_OUTPUT(L"Error loading musique.mp3" << std::endl);
        return;
    }

    SetBPM(260.f);
	SetupTexts();
	SetHitAreas();

    musicStarted = false;
    beatClock.restart();

    firstNote = noteDataList[0].time;
    CONSOLE_OUTPUT(firstNote << std::endl);
}


void MusicScript::LoadNotesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        CONSOLE_OUTPUT(L"Failed to open file: " << filename.c_str() << std::endl);
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string temp;
        int x, y;
        float time;

        std::getline(ss, temp, ','); x = std::stof(temp);
        std::getline(ss, temp, ','); y = std::stof(temp);
        std::getline(ss, temp, ','); time = std::stof(temp) / 1000.0f;

        noteDataList.push_back({ x, y, time });
    }

    CONSOLE_OUTPUT(L"Loaded " << noteDataList.size() << L" notes from " << filename.c_str() << std::endl);
}

void MusicScript::OnFixedUpdate()
{
}

void MusicScript::OnUpdate()
{
    float currentTime = beatClock.getElapsedTime().asSeconds();

    if (!musicStarted)
    {

        float songOffset = ((hitRect.getPosition().y - 60.f) / (FALL_SPEED * AR));

        if (currentTime + (noteDataList[0].time / 32) >= songOffset)
        {
            music.play();
            CONSOLE_OUTPUT(currentTime << std::endl);
            musicStarted = true;
        }
    }

    float beatNumber = currentTime / SECONDS_PER_BEAT;
    int closestBeat = static_cast<int>(beatNumber + 0.5f);
    float expectedTime = closestBeat * SECONDS_PER_BEAT;

    float realFallSpeed = FALL_SPEED * AR;

    static sf::Clock frameClock;
    float deltaTime = frameClock.restart().asSeconds();

    while (!noteDataList.empty() && noteDataList.front().time <= currentTime)
    {
        NoteData note = noteDataList.front();
        noteDataList.erase(noteDataList.begin());

        BeatCircle newCircle;
        newCircle.shape = sf::CircleShape(25.f);
        newCircle.shape.setFillColor(sf::Color::White);
        newCircle.shape.setPosition(sf::Vector2f(1920.f / 2, 0.f));
        newCircle.spawnTime = note.time;

        fallingCircles.push_back(newCircle);
    }

    for (auto& beatCircle : fallingCircles)
    {
        beatCircle.shape.move(sf::Vector2f(0.f, FALL_SPEED * AR * deltaTime));

		float circleY = beatCircle.shape.getPosition().y;

		if (circleY > 850)
		{
			fallingCircles.erase(fallingCircles.begin());
			break;
		}
    }

    bool sKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool dKeyNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    if ((sKeyNow && !sKeyPressed) || (dKeyNow && !dKeyPressed))
    {
        sKeyPressed = sKeyNow;
        dKeyPressed = dKeyNow;

        for (auto it = fallingCircles.begin(); it != fallingCircles.end();)
        {
            sf::CircleShape& circle = it->shape;
            float spawnTime = it->spawnTime;

            float circleY = circle.getPosition().y;
            float hitY = hitRect.getPosition().y;

            float realFallSpeed = FALL_SPEED * AR;
            float hitExpectedTime = spawnTime + (hitY / realFallSpeed);

            if (std::abs(circleY - hitY) <= 150.0f)
            {
                float timeDifference = std::abs(currentTime - hitExpectedTime);
                if (timeDifference <= TIMING_WINDOW)
                {
                    CONSOLE_OUTPUT(L"Perfect hit!" << std::endl);
                    IncreaseCombo();
                }
                else
                {
                    CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
                    ResetCombo();
                }
                it = fallingCircles.erase(it);
                break;
            }
            else
            {
                if (circleY > 900)
                {
                    CONSOLE_OUTPUT(L"Missed!" << std::endl);
                    ResetCombo();
                    it = fallingCircles.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }

    if (!sKeyNow) sKeyPressed = false;
    if (!dKeyNow) dKeyPressed = false;
}

void MusicScript::OnDisable()
{
    music.stop();
}

void MusicScript::OnRender(RenderWindow* window)
{
    window->draw(hitRect);
	window->draw(hitCircle);
	window->draw(BPMText);

    for (const auto& beatCircle : fallingCircles)
    {
        window->draw(beatCircle.shape);
    }
    ShowCombo(*window);
}

void MusicScript::ShowCombo(sf::RenderWindow& window) {
    comboText.setString("Combo: " + std::to_string(combo));
    maxComboText.setString("Max Combo: " + std::to_string(maxCombo));

    window.draw(comboText);
    window.draw(maxComboText);
}

void MusicScript::IncreaseCombo() {
    combo++;
    if (combo > maxCombo) {
        maxCombo = combo;
    }
}

void MusicScript::ResetCombo() {
    combo = 0;
}