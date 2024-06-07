#pragma once

#include <SFML/Graphics.hpp>
#include "gamesystem.hpp"
using namespace sf;
enum class Scenes { MENU, SETTING, GAME, AITESTING };

class MenuScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    sf::Vector2f buttonOffset{10.0f, 5.0f};
    // UI Elements and positions
    sf::RectangleShape titleOutline;
    sf::Text titleText;
    sf::Vector2f titlePosition{600.0f, 70.0f};
    sf::RectangleShape playButton;
    sf::Text playText;
    sf::Vector2f playPosition{600.0f, 300.0f};
    sf::RectangleShape aiButton;
    sf::Text aiText;
    sf::Vector2f aiPosition{600.0f, 450.0f};
public:
    MenuScene(sf::RenderWindow& window, sf::Font& font);
    void draw(Scenes* mState);
    void handleEvent(sf::Event);
};

class SettingScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    // UI Textures
    sf::Texture returnButtonTexture;
    sf::Texture smallButtonTexture;
    sf::Texture BackTextWhite;
    sf::Texture BackTextBlack;
    // UI Elements and positions
    sf::Sprite returnButton;
    sf::Sprite playButton;
    sf::Vector2f returnPosition{10.0f, 10.0f};
    sf::Text playerPlayText;
    sf::Vector2f playerPlayPosition{160.0f, 10.0f};
    sf::Text aiPlayText;
    sf::Vector2f aiPlayPosition{570.0f, 10.0f};
    sf::Text playText;
    sf::Text backText;
    sf::Vector2f playPosition{390.0f, 540.0f};
    sf::Sprite smallButton;
    std::array<sf::Text, 12> smallButtonText;
    std::array<sf::String, 12> smallButtonString{"2", "3", "4", "5", "2", "3", "4", "5", "Certainty", "Omniscient", "Rule-Based", "Hat-Principle"};
    std::array<sf::Vector2f, 12> smallButtonPosition{sf::Vector2f(160.0f, 230.0f), sf::Vector2f(270.0f, 230.0f), sf::Vector2f(160.0f, 340.0f), sf::Vector2f(270.0f, 340.0f), 
                                                    sf::Vector2f(600.0f, 230.0f), sf::Vector2f(710.0f, 230.0f), sf::Vector2f(820.0f, 230.0f), sf::Vector2f(930.0f, 230.0f), 
                                                    sf::Vector2f(600.0f, 340.0f), sf::Vector2f(710.0f, 340.0f), sf::Vector2f(820.0f, 340.0f), sf::Vector2f(930.0f, 340.0f)};
    sf::RectangleShape seperatorLine;
    sf::Vector2f seperatorLinePosition{470.0f, 0.0f};
    sf::Vector2f seperatorLineSize{10.0f, 40.0f};
    float seperatorLineOffset = 15.0f;
    int seperatorLineNumber = 10;

    RectangleShape Boarder1;
    RectangleShape Boarder2;


public:
    
    SettingScene(sf::RenderWindow& window, sf::Font& font);
    void draw(Scenes* mState);
    void handleEvent(sf::Event);
};

class GameScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    // UI Textures
    // UI Elements and positions
public:
    GameScene(sf::RenderWindow& window, sf::Font& font);
    void draw();
    void handleEvent(sf::Event);
};

class AITestingScene
{
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    // UI Textures
    // UI Elements and positions
public:
    AITestingScene(sf::RenderWindow& window, sf::Font& font);
    void draw();
    void handleEvent(sf::Event);
};