// Copyright 2023 Bikash Shrestha
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CelestialBody.hpp"
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <T> <t> <filename>\n";
        return 1;
    }

    double totaltime = std::stod(argv[1]);
    double ctime = std::stod(argv[2]);
    std::string filename = argv[3];

    double t = 0.0;
    const int windowSize = 512;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "The Solar System");

    Universe universe;
    double uniRadius;
    int n;

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << '\n';
        return 1;
    }

    inFile >> n >> uniRadius;
    universe = Universe(uniRadius, windowSize, n, inFile);
    inFile.close();

    sf::Clock clock;
    bool isClockRunning = true;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("interstellar.wav")) {
        std::cerr << "Unable to load sound effect!\n";
        return 1;
    }
    sf::Sound soundEffect;
    soundEffect.setBuffer(buffer);
    soundEffect.play();

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Unable to load font!\n";
        return 1;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, 10);

    // Load the background texture
    sf::Texture backgroundTexture;

    // Create a sprite for the background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize) / backgroundTexture.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (t < totaltime && universe.isMoving()) {
            universe.step(ctime);
            t += ctime;
            sf::Time elapsed = clock.getElapsedTime();
            std::stringstream ss;
            ss << "Elapsed Time: " << elapsed.asSeconds() << "s";
            timeText.setString(ss.str());
        } else if (isClockRunning) {
            isClockRunning = false;
            soundEffect.stop();
        }

        window.clear();
        window.draw(universe);
        window.draw(timeText);
        window.display();
    }

    std::cout << universe << std::endl;
    return 0;
}
