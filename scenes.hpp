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
                                                     sf::Vector2f(540.0f, 130.0f), sf::Vector2f(540.0f, 230.0f), sf::Vector2f(540.0f, 330.0f), sf::Vector2f(540.0f, 430.0f),
                                                     sf::Vector2f(650.0f, 130.0f), sf::Vector2f(650.0f, 230.0f), sf::Vector2f(650.0f, 330.0f), sf::Vector2f(650.0f, 430.0f)};
    sf::RectangleShape seperatorLine;
    sf::Vector2f seperatorLinePosition{470.0f, 0.0f};
    sf::Vector2f seperatorLineSize{10.0f, 40.0f};
    float seperatorLineOffset = 15.0f;
    int seperatorLineNumber = 10;

    RectangleShape Boarder1;
    RectangleShape Boarder2;


public:
    static PlayerCount playerGameCount;
    static PlayerCount aiGameCount;
    static AITypes aiGameType;
    
    SettingScene(sf::RenderWindow& window, sf::Font& font);
    void draw(Scenes* mState);
    void handleEvent(sf::Event);
};

class GameScene
{
    bool showFrontCard = true;
    sf::RenderWindow& mWindow;
    sf::Font& mFont;
    // UI Textures
    sf::Texture BackTextWhite;
    sf::Texture BackTextBlack;
    // UI Elements and positions
    // RETURN BUTTON
    sf::Sprite returnButton;
    sf::Vector2f returnPosition{10.0f, 10.0f};
    // LOG OUTLINE
    sf::RectangleShape logOutline;
    sf::Vector2f logOutlinePosition{10.0f, 180.0f};
    sf::Vector2f logOutlineSize{350.0f, 485.0f};
    // SWITCH CARD BUTTON
    sf::RectangleShape switchButton;
    sf::Text switchText;
    sf::Vector2f switchPosition{240.0f, 10.0f};
    sf::Vector2f switchSize{130.0f, 60.0f};
    sf::Vector2f switchTextOffset{11.0f, 7.0f};
    // CARDS
    sf::RectangleShape card;
    sf::RectangleShape cardsOutlineCollider;
    sf::Text cardText;
    sf::Vector2f cardAIPosition{390.0f, 10.0f};
    sf::Vector2f cardPlayerPosition{390.0f, 585.0f};
    sf::Vector2f cardSize{80.0f, 80.0f};
    sf::Vector2f cardOffset{10.0f, 10.0f};
    sf::Vector2f cardTextOffset{16.0f, -16.0f};
    // MINI HINTS WITHIN CARDS
    sf::RectangleShape miniHint;
    sf::RectangleShape miniLine;
    sf::Text miniText;
    sf::Vector2f miniHintPosition{11.0f, 16.0f};
    sf::Vector2f miniHintSize{10.0f, 16.0f};
    sf::Vector2f miniLineSize{19.0f, 2.0f};
    sf::Vector2f miniHintOffset{2.0f, 16.0f};
    sf::Vector2f miniHintTextOffset{0.0f, -4.5f};
    // AIs ID
    sf::Text aiIdText;
    // HINT BUTTONS
    sf::RectangleShape hintButton;
    sf::Text hintText;
    sf::Vector2f hintPosition{390.0f, 380.0f};
    sf::Vector2f hintSize{80.0f, 30.0f};
    sf::Vector2f hintTextOffset{28.0f, -13.0f};
    // GAMEPLAY BUTTONS
    sf::RectangleShape gameplayPlayButton;
    sf::Text gameplayPlayText;
    sf::Vector2f gameplayPlayPosition{430.0f, 510.0f};
    sf::Vector2f gameplayPlaySize{130.0f, 60.0f};
    sf::Vector2f gameplayPlayTextOffset{29.0f, 7.0f};
    sf::RectangleShape gameplayDiscardButton;
    sf::Text gameplayDiscardText;
    sf::Vector2f gameplayDiscardPosition{570.0f, 510.0f};
    sf::Vector2f gameplayDiscardSize{130.0f, 60.0f};
    sf::Vector2f gameplayDiscardTextOffset{2.0f, 7.0f};
    sf::RectangleShape gameplayHintButton;
    sf::Text gameplayHintText;
    sf::Vector2f gameplayHintPosition{750.0f, 470.0f};
    sf::Vector2f gameplayHintSize{80.0f, 60.0f};
    sf::Vector2f gameplayHintTextOffset{4.0f, 7.0f};
    // GAME INFOS OUTLINE
    sf::RectangleShape infosOutline;
    sf::Vector2f infosOutlinePosition{940.0f, 10.0f};
    sf::Vector2f infosOutlineSize{250.0f, 130.0f};
    sf::RectangleShape infosLine1;
    sf::Vector2f infosLine1Position{940.0f, 72.5f};
    sf::Vector2f infosLine1Size{125.0f, 5.0f};
    sf::RectangleShape infosLine2;
    sf::Vector2f infosLine2Position{1062.5f, 10.0f};
    sf::Vector2f infosLine2Size{5.0f, 130.0f};
    // GAME INFOS TURN AND SCORE
    sf::Text infosTurnText;
    sf::Vector2f infosTurnTextPosition{940.0f, 10.0f};
    sf::Vector2f infosTurnTextOffset{0.0f, 0.0f};
    sf::Text infosScoreText;
    sf::Vector2f infosScoreTextPosition{940.0f, 77.5f};
    sf::Vector2f infosScoreTextOffset{0.0f, 0.0f};
    // GAME INFOS TOKENS
    sf::CircleShape infosTokenBlue;
    sf::Vector2f infosTokenBluePosition{1077.5f, 20.0f};
    float infosTokenBlueRadius = 21.25f;
    sf::CircleShape infosTokenRed;
    sf::Vector2f infosTokenRedPosition{1077.5f, 87.5f};
    float infosTokenRedRadius = 21.25f;
    sf::Text infosTokenBlueText;
    sf::Vector2f infosTokenBlueTextPosition{1130.0f, 10.0f};
    sf::Vector2f infosTokenBlueTextOffset{0.0f, 0.0f};
    sf::Text infosTokenRedText;
    sf::Vector2f infosTokenRedTextPosition{1130.0f, 77.5f};
    sf::Vector2f infosTokenRedTextOffset{0.0f, 0.0f};
    // DISCARDED PILE
    sf::RectangleShape discardOutline;
    sf::Vector2f discardOutlinePosition{860.0f, 180.0f};
    sf::Vector2f discardOutlineSize{330.0f, 485.0f};
public:
    GameSystem game;
    GameScene(sf::RenderWindow& window, sf::Font& font);
    void setup();
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