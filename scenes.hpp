#pragma once

#include <SFML/Graphics.hpp>
#include "gamesystem.hpp"

enum class Scenes { MENU, GAME };

class MenuScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    // UI Textures
    sf::Texture playTexture;
    sf::Texture aiTexture;
    // UI Elements and positions
    sf::Text titleText;
    sf::Vector2f titlePosition{420.0f, 70.0f};
    sf::Sprite playButton;
    sf::Text playText;
    sf::Vector2f playPosition{250.0f, 300.0f};
    sf::Sprite aiButton;
    sf::Text aiText;
    sf::Vector2f aiPosition{250.0f, 450.0f};
public:
    MenuScene(sf::RenderWindow& window, sf::Font& font);
    void draw();
    void handleEvent(sf::Event);
};

class GameScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
public:
    GameScene(sf::RenderWindow& window, sf::Font& font);
    void draw();
    void handleEvent(sf::Event);
};