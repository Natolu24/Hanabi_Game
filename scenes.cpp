#include "scenes.hpp"

// Text offset that need to be multiplied by the text character size to then displace the position
sf::Vector2f TEXT_OFFSET{0.0f, -0.23f};

MenuScene::MenuScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font)
{
    // Setup all UI elements
    // Title "Hanabi"
    titlePosition.x -= (100.0f*0.6f)*(6.0f/2.0f); // displace base position (center of the text) by half of the text length to the left (left side of the text)
    titleOutline.setPosition(titlePosition - buttonOffset); // set position, and add an offset (margin)
    titleOutline.setSize(sf::Vector2f((100.0f*0.6f)*6.0f, 100.0f) + buttonOffset*2.0f); // set size of button == size of text + offset/margin
    titleOutline.setFillColor(sf::Color::Transparent); // to get juste the outline, need that the space within the outline be transparent
    titleOutline.setOutlineThickness(15);
    titleOutline.setOutlineColor(sf::Color::White);
    titleText.setFont(mFont);
    titleText.setString("HANABI");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(titlePosition + TEXT_OFFSET*100.0f); // text position + offset to make text be centered (offset multiplied by character size)

    // Button "Play Game"
    playPosition.x -= (80.0f*0.6f)*(9.0f/2.0f);
    playButton.setPosition(playPosition - buttonOffset);
    playButton.setSize(sf::Vector2f((80.0f*0.6f)*9.0f, 80.0f) + buttonOffset*2.0f);
    playButton.setFillColor(sf::Color::White);
    playText.setFont(mFont);
    playText.setString("Play Game");
    playText.setCharacterSize(80);
    playText.setFillColor(sf::Color::Black);
    playText.setPosition(playPosition + TEXT_OFFSET*80.0f);

    // Button "AIs Testing"
    aiPosition.x -= (80.0f*0.6f)*(11.0f/2.0f);
    aiButton.setPosition(aiPosition - buttonOffset);
    aiButton.setSize(sf::Vector2f((80.0f*0.6f)*11.0f, 80.0f) + buttonOffset*2.0f);
    aiButton.setFillColor(sf::Color::White);
    aiText.setFont(mFont);
    aiText.setString("AIs Testing");
    aiText.setCharacterSize(80);
    aiText.setFillColor(sf::Color::Black);
    aiText.setPosition(aiPosition + TEXT_OFFSET*80.0f);
}

void MenuScene::draw() 
{
    mWindow.clear(sf::Color::Black);
    mWindow.draw(titleText);
    mWindow.draw(titleOutline);
    mWindow.draw(playButton);
    mWindow.draw(playText);
    mWindow.draw(aiButton);
    mWindow.draw(aiText);
    mWindow.display();
}

void MenuScene::handleEvent(sf::Event)
{

}

SettingScene::SettingScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font)
{
    // Load all UI textures
    if (!returnButtonTexture.loadFromFile("assets/default_texture.png"))
    {
        std::cout << "Error while loading return button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!smallButtonTexture.loadFromFile("assets/default_texture.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup all UI elements
    returnButton.setTexture(returnButtonTexture);
    returnButton.setTextureRect({0, 0, 100, 100}); // Default Texture TMP Size Fixed
    returnButton.setPosition(returnPosition);

    smallButton.setTexture(smallButtonTexture);
    smallButton.setTextureRect({0, 0, 100, 100}); // Default Texture TMP Size Fixed

    playerPlayText.setFont(mFont);
    playerPlayText.setString("Player");
    playerPlayText.setCharacterSize(60);
    playerPlayText.setFillColor(sf::Color::White);
    playerPlayText.setPosition(playerPlayPosition);

    aiPlayText.setFont(mFont);
    aiPlayText.setString("AIs Only Game");
    aiPlayText.setCharacterSize(60);
    aiPlayText.setFillColor(sf::Color::White);
    aiPlayText.setPosition(aiPlayPosition);

    playText.setFont(mFont);
    playText.setString("PLAY");
    playText.setCharacterSize(80);
    playText.setFillColor(sf::Color::White);
    playText.setStyle(sf::Text::Bold);
    playText.setPosition(playPosition);
}

void SettingScene::draw() 
{
    mWindow.clear(sf::Color::Black);
    mWindow.draw(returnButton);
    mWindow.draw(playerPlayText);
    mWindow.draw(aiPlayText);
    mWindow.draw(playText);
    for (int i = 0; i < 12; i++)
    {
        smallButton.setPosition(smallButtonPosition[i]);
        mWindow.draw(smallButton);
        smallButtonText[i].setPosition(smallButtonPosition[i]);
        smallButtonText[i].setString(smallButtonString[i]);
        mWindow.draw(smallButtonText[i]);
    }
    seperatorLine.setSize(seperatorLineSize);
    for (int i = 0; i < seperatorLineNumber; i++)
    {
        seperatorLine.setPosition(seperatorLinePosition + sf::Vector2f(10.0f, (seperatorLineOffset + seperatorLineSize.y) * i));
        mWindow.draw(seperatorLine);
    }
    mWindow.display();
}

void SettingScene::handleEvent(sf::Event)
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

AITestingScene::AITestingScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font) {}

void AITestingScene::draw() 
{
    mWindow.clear(sf::Color::Black);
    mWindow.display();
}

void AITestingScene::handleEvent(sf::Event)
{

}
