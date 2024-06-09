#pragma once

#include <SFML/Graphics.hpp>
#include "scenes.hpp"

class Application
{
    sf::RenderWindow& mWindow;
    sf::Font mFont;
public:
    // The state determining wich current scene is running
    Scenes mState = Scenes::GAME;
    // All the different scenes of the application
    MenuScene mMenu;
    SettingScene mSetting;
    GameScene mGame;
    AITestingScene mAITesting;
    Application(sf::RenderWindow& window);
    void run();
};