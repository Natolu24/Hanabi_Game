#pragma once

#include <SFML/Graphics.hpp>
#include "scenes.hpp"

class Application
{
    sf::RenderWindow& mWindow;
    sf::Font mFont;
    // The state determining wich current scene is running
    Scenes mState = Scenes::MENU;
    // All the different scenes of the application
    MenuScene mMenu;
    GameScene mGame;
public:
    Application(sf::RenderWindow& window);
    void run();
};