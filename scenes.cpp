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

void MenuScene::draw(Scenes* mState)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
    if (playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
    
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            *mState = Scenes::SETTING;
        }
    }
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

PlayerCount SettingScene::playerGameCount = PlayerCount::FivePlayers; // tmp value, need to be set to null
PlayerCount SettingScene::aiGameCount = PlayerCount::null; // tmp value, need to be set to null
AITypes SettingScene::aiGameType = AITypes::null; // tmp value, need to be set to null

SettingScene::SettingScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font)
{
    // Load all UI textures
    if (!returnButtonTexture.loadFromFile("assets/default_texture_white.png"))
    {
        std::cout << "Error while loading return button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!smallButtonTexture.loadFromFile("assets/default_texture.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!BackTextBlack.loadFromFile("assets/1.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);

    }
    if (!BackTextWhite.loadFromFile("assets/2.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup all UI element
   // returnButton.setTexture(returnButtonTexture);
   // returnButton.setTextureRect({0, 0, 100, 100}); // Default Texture TMP Size Fixed
    returnButton.setPosition(10,10);


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
    playText.setFillColor(sf::Color::Black);
    playText.setStyle(sf::Text::Bold);
    playText.setPosition(385,550);
    playButton.setTexture(smallButtonTexture);
    playButton.setTextureRect({ 0, 0, 240, 80 }); // Default Texture TMP Size Fixed
    playButton.setPosition(365, 565);

    Boarder1.setSize(Vector2f(250, 70));
    Boarder1.setPosition(145, 20);
    Boarder1.setFillColor(sf::Color::Transparent); // Hollow inside
    Boarder1.setOutlineThickness(5); // Thickness of the border
    Boarder1.setOutlineColor(sf::Color::White); // Color of the border

    Boarder2.setSize(Vector2f(500, 70));
    Boarder2.setPosition(550, 20);
    Boarder2.setFillColor(sf::Color::Transparent); // Hollow inside
    Boarder2.setOutlineThickness(5); // Thickness of the border
    Boarder2.setOutlineColor(sf::Color::White); // Color of the border
}

void SettingScene::draw(Scenes* mState)
{
    sf::Vector2i mousePosInWindow = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePos = mWindow.mapPixelToCoords(mousePosInWindow);

    if (returnButton.getGlobalBounds().contains(mousePos))
    {
        returnButton.setTexture(BackTextBlack);
        returnButton.setTextureRect({ 0, 0, 100, 100 }); // Default Texture TMP Size Fixed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            *mState = Scenes::MENU;
        }
    }
    else
    {
        returnButton.setTexture(BackTextWhite);
        returnButton.setTextureRect({ 0, 0, 100, 100 }); // Default Texture TMP Size Fixed
    }

    if (playButton.getGlobalBounds().contains(mousePos))
    {
        playButton.setTexture(smallButtonTexture);
        playButton.setTextureRect({ 0, 0, 240, 80 }); // Default Texture TMP Size Fixed
    }
    else
    {
        playButton.setTexture(returnButtonTexture);
        playButton.setTextureRect({ 0, 0, 240, 80 }); // Default Texture TMP Size Fixed
    }

    mWindow.clear(sf::Color::Black);
    mWindow.draw(returnButton);
    mWindow.draw(playButton);
    mWindow.draw(playerPlayText);
    mWindow.draw(aiPlayText);
    mWindow.draw(Boarder1);
    mWindow.draw(Boarder2);
    mWindow.draw(playText);
    for (int i = 0; i < 12; i++)
    {
        smallButton.setPosition(smallButtonPosition[i]);
        smallButton.setTexture(smallButtonTexture);
        if (i >= 0 && i <= 7)
            smallButton.setTextureRect({ 0,0,80,80 });
        if (i >= 8 && i <= 11)
            smallButton.setTextureRect({ 0,0,500,80 });

        if (smallButton.getGlobalBounds().contains(mousePos))
        {

            if (i >= 0 && i <= 3)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    smallButtonString[i] = '2';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    smallButtonString[i] = '3';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                    smallButtonString[i] = '4';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
                    smallButtonString[i] = '5';
                }
            }
            else if (i >= 4 && i <= 7)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    smallButtonString[i] = '2';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    smallButtonString[i] = '3';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                    smallButtonString[i] = '4';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
                    smallButtonString[i] = '5';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
                    smallButtonString[i] = '6';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
                    smallButtonString[i] = '7';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
                    smallButtonString[i] = '8';
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
                    smallButtonString[i] = '9';
                }
            }
        }
        else
        {
            smallButton.setTexture(returnButtonTexture);
            if (i >= 0 && i <= 7)
                smallButton.setTextureRect({ 0,0,80,80 });
            if (i >= 8 && i <= 11)
                smallButton.setTextureRect({ 0,0,500,80 });
        }
        mWindow.draw(smallButton);

        smallButtonText[i].setFont(mFont);
        smallButtonText[i].setPosition(smallButtonPosition[i].x+20, smallButtonPosition[i].y );
        smallButtonText[i].setString(smallButtonString[i]);
        smallButtonText[i].setCharacterSize(60);
        smallButtonText[i].setFillColor(sf::Color::Black);
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

GameScene::GameScene(sf::RenderWindow& window, sf::Font& font) : mWindow(window), mFont(font), game(SettingScene::playerGameCount) // TMP TO BE DELETED
{
    if (!BackTextBlack.loadFromFile("assets/1.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!BackTextWhite.loadFromFile("assets/2.png"))
    {
        std::cout << "Error while loading small button texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    returnButton.setPosition(10,10);
    returnButton.setTextureRect({ 0, 0, 100, 100 });

    logOutline.setPosition(logOutlinePosition);
    logOutline.setSize(logOutlineSize);
    logOutline.setFillColor(sf::Color::Transparent);
    logOutline.setOutlineColor(sf::Color(124, 124, 124));
    logOutline.setOutlineThickness(5.0f);

    switchButton.setPosition(switchPosition);
    switchButton.setSize(switchSize);
    switchButton.setFillColor(sf::Color::White);
    switchText.setFont(mFont);
    switchText.setString("Switch");
    switchText.setPosition(switchPosition + switchTextOffset);
    switchText.setCharacterSize(30);
    switchText.setFillColor(sf::Color::Black);

    miniHint.setSize(miniHintSize);
    miniLine.setSize(miniLineSize);
    miniLine.setFillColor(sf::Color::Black);
    miniLine.setRotation(45.0f);
    miniText.setFont(mFont);
    miniText.setCharacterSize(18);
    miniText.setFillColor(sf::Color::Black);

    card.setSize(cardSize);
    card.setOutlineColor(sf::Color(124, 124, 124));
    cardsOutlineCollider.setFillColor(sf::Color::Transparent);
    cardsOutlineCollider.setOutlineColor(sf::Color(124, 124, 124));
    cardsOutlineCollider.setOutlineThickness(5.0f);
    cardText.setFont(mFont);
    cardText.setCharacterSize(80);
    cardText.setFillColor(sf::Color::Black);
    aiIdText.setFont(mFont);
    aiIdText.setCharacterSize(60);
    aiIdText.setFillColor(sf::Color::White);

    hintButton.setSize(hintSize);
    hintButton.setOutlineColor(sf::Color(124, 124, 124));
    hintText.setFont(mFont);
    hintText.setCharacterSize(40);
    hintText.setFillColor(sf::Color::Black);

    gameplayPlayButton.setPosition(gameplayPlayPosition);
    gameplayPlayButton.setSize(gameplayPlaySize);
    gameplayPlayButton.setFillColor(sf::Color::White);
    gameplayPlayText.setFont(mFont);
    gameplayPlayText.setString("Play");
    gameplayPlayText.setPosition(gameplayPlayPosition + gameplayPlayTextOffset);
    gameplayPlayText.setCharacterSize(30);
    gameplayPlayText.setFillColor(sf::Color::Black);

    gameplayDiscardButton.setPosition(gameplayDiscardPosition);
    gameplayDiscardButton.setSize(gameplayDiscardSize);
    gameplayDiscardButton.setFillColor(sf::Color::White);
    gameplayDiscardText.setFont(mFont);
    gameplayDiscardText.setString("Discard");
    gameplayDiscardText.setPosition(gameplayDiscardPosition + gameplayDiscardTextOffset);
    gameplayDiscardText.setCharacterSize(30);
    gameplayDiscardText.setFillColor(sf::Color::Black);

    gameplayHintButton.setPosition(gameplayHintPosition);
    gameplayHintButton.setSize(gameplayHintSize);
    gameplayHintButton.setFillColor(sf::Color::White);
    gameplayHintText.setFont(mFont);
    gameplayHintText.setString("Hint");
    gameplayHintText.setPosition(gameplayHintPosition + gameplayHintTextOffset);
    gameplayHintText.setCharacterSize(30);
    gameplayHintText.setFillColor(sf::Color::Black);

    infosOutline.setPosition(infosOutlinePosition);
    infosOutline.setSize(infosOutlineSize);
    infosOutline.setFillColor(sf::Color::Transparent);
    infosOutline.setOutlineColor(sf::Color(124, 124, 124));
    infosOutline.setOutlineThickness(5.0f);
    infosLine1.setPosition(infosLine1Position);
    infosLine1.setSize(infosLine1Size);
    infosLine1.setFillColor(sf::Color(124, 124, 124));
    infosLine2.setPosition(infosLine2Position);
    infosLine2.setSize(infosLine2Size);
    infosLine2.setFillColor(sf::Color(124, 124, 124));

    infosTurnText.setFont(mFont);
    infosTurnText.setPosition(infosTurnTextPosition + infosTurnTextOffset);
    infosTurnText.setCharacterSize(40);
    infosTurnText.setFillColor(sf::Color::White);
    infosScoreText.setFont(mFont);
    infosScoreText.setPosition(infosScoreTextPosition + infosScoreTextOffset);
    infosScoreText.setCharacterSize(40);
    infosScoreText.setFillColor(sf::Color::White);

    infosTokenBlue.setPosition(infosTokenBluePosition);
    infosTokenBlue.setRadius(infosTokenBlueRadius);
    infosTokenBlue.setFillColor(sf::Color::Blue);
    infosTokenRed.setPosition(infosTokenRedPosition);
    infosTokenRed.setRadius(infosTokenRedRadius);
    infosTokenRed.setFillColor(sf::Color::Red);
    infosTokenBlueText.setFont(mFont);
    infosTokenBlueText.setPosition(infosTokenBlueTextPosition + infosTokenBlueTextOffset);
    infosTokenBlueText.setCharacterSize(40);
    infosTokenBlueText.setFillColor(sf::Color::White);
    infosTokenRedText.setFont(mFont);
    infosTokenRedText.setPosition(infosTokenRedTextPosition + infosTokenRedTextOffset);
    infosTokenRedText.setCharacterSize(40);
    infosTokenRedText.setFillColor(sf::Color::White);

    discardOutline.setPosition(discardOutlinePosition);
    discardOutline.setSize(discardOutlineSize);
    discardOutline.setFillColor(sf::Color::Transparent);
    discardOutline.setOutlineColor(sf::Color(124, 124, 124));
    discardOutline.setOutlineThickness(5.0f);
}

void GameScene::setup()
{
    //mGame.setup()


}

void GameScene::draw()
{
    sf::Vector2i mousePosInWindow = sf::Mouse::getPosition(mWindow);
    sf::Vector2f mousePos = mWindow.mapPixelToCoords(mousePosInWindow);

    if (returnButton.getGlobalBounds().contains(mousePos))
    {
        returnButton.setTexture(BackTextBlack);
    }
    else
    {
        returnButton.setTexture(BackTextWhite);
    }
    
    mWindow.clear(sf::Color::Black);
    // Return Button
    mWindow.draw(returnButton);
    // Log
    mWindow.draw(logOutline);
    // Switch Cards Button
    if (switchButton.getGlobalBounds().contains(mousePos))
    {
        switchButton.setFillColor(sf::Color(124, 124, 124));
    }
    else
    {
        switchButton.setFillColor(sf::Color::White);
    }
    mWindow.draw(switchButton);
    mWindow.draw(switchText);
    // AIs Cards
    card.setOutlineThickness(0.0f); // reset thickness in case previous modification is still active
    if (showFrontCard) // Show the card itself of the others AIs
    {
        for (int lin = 0; lin < int(game.playersNumber)-1; lin++)
        {
            std::vector<Card> pCards = game.getPlayerCards(lin+2);
            for (int col = 0; col < int(pCards.size())+1; col++)
            {
                sf::Vector2f offsetPosition((cardSize.x + cardOffset.x) * float(col), (cardSize.y + cardOffset.y) * float(lin));
                if (col == int(pCards.size()))
                {
                    aiIdText.setPosition(cardAIPosition + offsetPosition);
                    aiIdText.setString("#" + std::to_string(lin+1));
                    mWindow.draw(aiIdText);
                    break;
                }
                card.setPosition(cardAIPosition + offsetPosition);
                switch(pCards[col].color)
                {
                    case CardAttribute::White:
                        card.setFillColor(sf::Color::White);
                        break;
                    case CardAttribute::Yellow:
                        card.setFillColor(sf::Color::Yellow);
                        break;
                    case CardAttribute::Blue:
                        card.setFillColor(sf::Color::Blue);
                        break;
                    case CardAttribute::Red:
                        card.setFillColor(sf::Color::Red);
                        break;
                    case CardAttribute::Green:
                        card.setFillColor(sf::Color::Green);
                        break;
                    default:
                        break;
                }
                cardText.setPosition(cardAIPosition + offsetPosition + cardTextOffset);
                switch(pCards[col].number)
                {
                    case CardAttribute::One:
                        cardText.setString("1");
                        break;
                    case CardAttribute::Two:
                        cardText.setString("2");
                        break;
                    case CardAttribute::Three:
                        cardText.setString("3");
                        break;
                    case CardAttribute::Four:
                        cardText.setString("4");
                        break;
                    case CardAttribute::Five:
                        cardText.setString("5");
                        break;
                    default:
                        break;
                }
                mWindow.draw(card);
                mWindow.draw(cardText);
            }
            sf::Vector2f colliderPosition(0.0f, (cardSize.y + cardOffset.y) * float(lin));
            sf::Vector2f colliderSize((cardSize.x + cardOffset.x) * 4 + cardSize.x, cardSize.y);
            cardsOutlineCollider.setPosition(cardAIPosition + colliderPosition);
            cardsOutlineCollider.setSize(colliderSize);
            if (cardsOutlineCollider.getGlobalBounds().contains(mousePos))
            {
                mWindow.draw(cardsOutlineCollider);
            }
        }
    }
    else // Otherwise show its "back", but mostly with the indirect hints given
    {
        card.setFillColor(sf::Color(200, 200, 200));
        for (int lin = 0; lin < int(game.playersNumber)-1; lin++)
        {
            std::vector<Card> pCards = game.getPlayerCards(lin+2);
            for (int col = 0; col < int(pCards.size())+1; col++)
            {
                sf::Vector2f offsetPosition((cardSize.x + cardOffset.x) * float(col), (cardSize.y + cardOffset.y) * float(lin));
                if (col == int(pCards.size()))
                {
                    aiIdText.setPosition(cardAIPosition + offsetPosition);
                    aiIdText.setString("#" + std::to_string(lin+1));
                    mWindow.draw(aiIdText);
                    break;
                }
                card.setPosition(cardAIPosition + offsetPosition);
                mWindow.draw(card);
                for (int i = 0; i < 5; i++) // Color Indirect Hints
                {
                    sf::Vector2f miniOffsetPosition(offsetPosition.x + (miniHintSize.x + miniHintOffset.x) * float(i), offsetPosition.y);
                    miniHint.setPosition(cardAIPosition + miniHintPosition + miniOffsetPosition);
                    switch(pCards[col].indirectAttributeHints[i+5])
                    {
                        case CardAttribute::White:
                            miniHint.setFillColor(sf::Color::White);
                            mWindow.draw(miniHint);
                            break;
                        case CardAttribute::Blue:
                            miniHint.setFillColor(sf::Color::Blue);
                            mWindow.draw(miniHint);
                            break;
                        case CardAttribute::Yellow:
                            miniHint.setFillColor(sf::Color::Yellow);
                            mWindow.draw(miniHint);
                            break;
                        case CardAttribute::Red:
                            miniHint.setFillColor(sf::Color::Red);
                            mWindow.draw(miniHint);
                            break;
                        case CardAttribute::Green:
                            miniHint.setFillColor(sf::Color::Green);
                            mWindow.draw(miniHint);
                            break;
                        default:
                            miniLine.setPosition(cardAIPosition + miniHintPosition + miniOffsetPosition);
                            mWindow.draw(miniLine);
                            break;
                    }
                }
                for (int i = 0; i < 5; i++) // Number Indirect Hints
                {
                    sf::Vector2f miniOffsetPosition(offsetPosition.x + (miniHintSize.x + miniHintOffset.x) * float(i), offsetPosition.y + miniHintSize.y + miniHintOffset.y);
                    if (pCards[col].indirectAttributeHints[i] != CardAttribute::null)
                    {
                        miniText.setPosition(cardAIPosition + miniHintPosition + miniOffsetPosition + miniHintTextOffset);
                        miniText.setString(std::to_string(i+1));
                        mWindow.draw(miniText);
                    }
                    else
                    {
                        miniLine.setPosition(cardAIPosition + miniHintPosition + miniOffsetPosition);
                        mWindow.draw(miniLine);

                    }
                }
            }
            sf::Vector2f colliderPosition(0.0f, (cardSize.y + cardOffset.y) * float(lin));
            sf::Vector2f colliderSize((cardSize.x + cardOffset.x) * 4 + cardSize.x, cardSize.y);
            cardsOutlineCollider.setPosition(cardAIPosition + colliderPosition);
            cardsOutlineCollider.setSize(colliderSize);
            if (cardsOutlineCollider.getGlobalBounds().contains(mousePos))
            {
                mWindow.draw(cardsOutlineCollider);
            }
        }
    }
    card.setFillColor(sf::Color(200, 200, 200)); // back side for player (light gray)
    // "Player" Cards
    for (int col = 0; col < int(game.p0.size()); col++)
    {
        sf::Vector2f offsetPosition((cardSize.x + cardOffset.x) * float(col), 0.0f);
        card.setPosition(cardPlayerPosition + offsetPosition);
        if (card.getGlobalBounds().contains(mousePos))
        {
            card.setOutlineThickness(5.0f);
        }
        else
        {
            card.setOutlineThickness(0.0f);
        }
        mWindow.draw(card);
        for (int i = 0; i < 5; i++) // Color Indirect Hints
        {
            sf::Vector2f miniOffsetPosition(offsetPosition.x + (miniHintSize.x + miniHintOffset.x) * float(i), offsetPosition.y);
            miniHint.setPosition(cardPlayerPosition + miniHintPosition + miniOffsetPosition);
            switch(game.p0[col].indirectAttributeHints[i+5])
            {
                case CardAttribute::White:
                    miniHint.setFillColor(sf::Color::White);
                    mWindow.draw(miniHint);
                    break;
                case CardAttribute::Blue:
                    miniHint.setFillColor(sf::Color::Blue);
                    mWindow.draw(miniHint);
                    break;
                case CardAttribute::Yellow:
                    miniHint.setFillColor(sf::Color::Yellow);
                    mWindow.draw(miniHint);
                    break;
                case CardAttribute::Red:
                    miniHint.setFillColor(sf::Color::Red);
                    mWindow.draw(miniHint);
                    break;
                case CardAttribute::Green:
                    miniHint.setFillColor(sf::Color::Green);
                    mWindow.draw(miniHint);
                    break;
                default:
                    miniLine.setPosition(cardAIPosition + miniHintPosition + miniOffsetPosition);
                    mWindow.draw(miniLine);
                    break;
            }
        }
        for (int i = 0; i < 5; i++) // Number Indirect Hints
        {
            sf::Vector2f miniOffsetPosition(offsetPosition.x + (miniHintSize.x + miniHintOffset.x) * float(i), offsetPosition.y + miniHintSize.y + miniHintOffset.y);
            if (game.p0[col].indirectAttributeHints[i] != CardAttribute::null)
            {
                miniText.setPosition(cardPlayerPosition + miniHintPosition + miniOffsetPosition + miniHintTextOffset);
                miniText.setString(std::to_string(i+1));
                mWindow.draw(miniText);
            }
            else
            {
                miniLine.setPosition(cardPlayerPosition + miniHintPosition + miniOffsetPosition);
                mWindow.draw(miniLine);

            }
        }
    }
    // Color Hint Buttons
    for (int col = 0; col < 5; col++)
    {
        sf::Vector2f offsetPosition((hintSize.x + cardOffset.x) * float(col), 0.0f);
        hintButton.setPosition(hintPosition + offsetPosition);
        switch(col)
        {
            case 0:
                hintButton.setFillColor(sf::Color::White);
                break;
            case 1:
                hintButton.setFillColor(sf::Color::Blue);
                break;
            case 2:
                hintButton.setFillColor(sf::Color::Yellow);
                break;
            case 3:
                hintButton.setFillColor(sf::Color::Red);
                break;
            case 4:
                hintButton.setFillColor(sf::Color::Green);
                break;
        }
        if (hintButton.getGlobalBounds().contains(mousePos))
        {
            hintButton.setOutlineThickness(5.0f);
        }
        else
        {
            hintButton.setOutlineThickness(0.0f);
        }
        mWindow.draw(hintButton);
    }
    // Number Hint Buttons
    hintButton.setFillColor(sf::Color(200, 200, 200));
    for (int col = 0; col < 5; col++)
    {
        sf::Vector2f offsetPosition((hintSize.x + cardOffset.x) * float(col), hintSize.y + 10.0f);
        hintButton.setPosition(hintPosition + offsetPosition);
        hintText.setPosition(hintPosition + offsetPosition + hintTextOffset);
        hintText.setString(std::to_string(col+1));
        if (hintButton.getGlobalBounds().contains(mousePos))
        {
            hintButton.setOutlineThickness(5.0f);
        }
        else
        {
            hintButton.setOutlineThickness(0.0f);
        }
        mWindow.draw(hintButton);
        mWindow.draw(hintText);
    }
    // Gameplay Play Button
    if (gameplayPlayButton.getGlobalBounds().contains(mousePos))
    {
        gameplayPlayButton.setFillColor(sf::Color(124, 124, 124));
    }
    else
    {
        gameplayPlayButton.setFillColor(sf::Color::White);
    }
    mWindow.draw(gameplayPlayButton);
    mWindow.draw(gameplayPlayText);
    // Gameplay Discard Button
    if (gameplayDiscardButton.getGlobalBounds().contains(mousePos))
    {
        gameplayDiscardButton.setFillColor(sf::Color(124, 124, 124));
    }
    else
    {
        gameplayDiscardButton.setFillColor(sf::Color::White);
    }
    mWindow.draw(gameplayDiscardButton);
    mWindow.draw(gameplayDiscardText);
    // Gameplay Hint Button
    if (gameplayHintButton.getGlobalBounds().contains(mousePos))
    {
        gameplayHintButton.setFillColor(sf::Color(124, 124, 124));
    }
    else
    {
        gameplayHintButton.setFillColor(sf::Color::White);
    }
    mWindow.draw(gameplayHintButton);
    mWindow.draw(gameplayHintText);
    // Infos Outlines
    mWindow.draw(infosOutline);
    mWindow.draw(infosLine1);
    mWindow.draw(infosLine2);
    // Infos Turn and Score
    infosTurnText.setString("T. " + std::to_string(game.turn));
    mWindow.draw(infosTurnText);
    if (game.score <= 9)
    {
        infosScoreText.setString(" " + std::to_string(game.score) + "/25"); // TODO : MAXSCORE THINGY
    }
    else
    {
        infosScoreText.setString(std::to_string(game.score) + "/25");
    }
    mWindow.draw(infosScoreText);
    // Infos Tokens
    mWindow.draw(infosTokenBlue);
    infosTokenBlueText.setString("x" + std::to_string(game.hintTokens));
    mWindow.draw(infosTokenBlueText);
    mWindow.draw(infosTokenRed);
    infosTokenRedText.setString("x" + std::to_string(game.errorTokens));
    mWindow.draw(infosTokenRedText);
    // Discard Pile
    mWindow.draw(discardOutline);

    mWindow.display();
}

void GameScene::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePosInWindow = sf::Mouse::getPosition(mWindow);
        sf::Vector2f mousePos = mWindow.mapPixelToCoords(mousePosInWindow);
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (switchButton.getGlobalBounds().contains(mousePos))
            {
                showFrontCard = !showFrontCard;
            }
        }
    }
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
