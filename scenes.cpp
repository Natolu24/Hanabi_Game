#include "scenes.hpp"

MenuScene::MenuScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font)
{
    // Load all UI textures
    if (!playTexture.loadFromFile("assets/default_texture.png"))
    {
        std::cout << "Error while loading play button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!aiTexture.loadFromFile("assets/default_texture.png"))
    {
        std::cout << "Error while loading AI Scores button texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup all UI elements
    titleText.setFont(mFont);
    titleText.setString("HANABI");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(titlePosition);

    playButton.setTexture(playTexture);
    playButton.setTextureRect({0, 0, 700, 100}); // Default Texture TMP Size Fixed
    playButton.setPosition(playPosition);

    playText.setFont(mFont);
    playText.setString("Play Game");
    playText.setCharacterSize(80);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(1200/2 - (80*0.6)*(9/2.0f), playPosition.y-8);

    aiButton.setTexture(aiTexture);
    aiButton.setTextureRect({0, 0, 700, 100}); // Default Texture TMP Size Fixed
    aiButton.setPosition(aiPosition);

    aiText.setFont(mFont);
    aiText.setString("AIs Testing");
    aiText.setCharacterSize(80);
    aiText.setFillColor(sf::Color::White);
    aiText.setPosition(1200/2 - (80*0.6)*(11/2.0f), aiPosition.y-8);
}

void MenuScene::draw() 
{
    mWindow.clear(sf::Color::Black);
    mWindow.draw(titleText);
    mWindow.draw(playButton);
    mWindow.draw(playText);
    mWindow.draw(aiButton);
    mWindow.draw(aiText);
    mWindow.display();
}

void MenuScene::handleEvent(sf::Event)
{

}

GameScene::GameScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font) {}

void GameScene::draw() 
{
    mWindow.clear(sf::Color::Black);
    mWindow.display();
}

void GameScene::handleEvent(sf::Event)
{

}