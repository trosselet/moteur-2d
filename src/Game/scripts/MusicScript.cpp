#include "pch.h"
#include "MusicScript.h"
#include <fstream>
#include <sstream>

void MusicScript::OnStart()
{
    LoadNotesFromFile("../../res/Beatmaps/4.txt");

    if (!music.openFromFile("../../res/Music/4.ogg"))
    {
        std::cerr << "Error loading musique.mp3" << std::endl;
        return;
    }

    musicStarted = false;
    beatClock.restart();

    hitRect.setFillColor(sf::Color::White);
    hitRect.setSize(sf::Vector2f(1920.f, 5.f));
    hitRect.setPosition(sf::Vector2(0.f, 800.f));

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

        float songOffset = (750.f / (FALL_SPEED * AR));
		CONSOLE_OUTPUT(noteDataList[0].time << " " << songOffset << std::endl);

        if (currentTime + (noteDataList[0].time / 64) >= songOffset)
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
        newCircle.shape.setPosition(sf::Vector2f(700, 0.f));
        newCircle.spawnTime = note.time;

        fallingCircles.push_back(newCircle);
    }

    for (auto& beatCircle : fallingCircles)
    {
        beatCircle.shape.move(sf::Vector2f(0.f, FALL_SPEED * AR * deltaTime));
    }

    if (GetAsyncKeyState('S') & 0x0001 || GetAsyncKeyState('D') & 0x0001)
    {
        for (auto it = fallingCircles.begin(); it != fallingCircles.end();)
        {
            sf::CircleShape& circle = it->shape;
            float spawnTime = it->spawnTime;

            float circleY = circle.getPosition().y;
            float hitY = hitRect.getPosition().y;

            float realFallSpeed = FALL_SPEED * AR;
            float hitExpectedTime = spawnTime + (hitY / realFallSpeed);

            if (std::abs(circleY - hitY) <= 65.0f )
            {
                float timeDifference = std::abs(currentTime - hitExpectedTime);
                if (timeDifference <= TIMING_WINDOW)
                {
                    CONSOLE_OUTPUT(L"Perfect hit!" << std::endl);
                    // ajouter des particules pour dire qu'on a  bien tapé
                }
                else
                {
                    CONSOLE_OUTPUT(L"Missed! (" << timeDifference << "s off)" << std::endl);
                    // same avec les miss 
                }

                CONSOLE_OUTPUT(circleY << " " << hitY << std::endl);
                it = fallingCircles.erase(it);
            }
            else
            {   
				if (circleY > 900)
				{
					CONSOLE_OUTPUT(L"Missed!" << std::endl);
					it = fallingCircles.erase(it);
				}
				else
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