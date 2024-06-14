#include "gamesystem.hpp"

Card::Card(CardAttribute number, CardAttribute color) : number(number), color(color) {}

void Card::addHint(CardAttribute hint, bool isDirectHint)
{
    if (isDirectHint) // is hint given directly to this card
    {
        if (int(hint) <= int(CardAttribute::Five)) // if number hint
        {
            for (int i = 1; i < 6; i++)
            {
                if (i == int(hint))
                {
                    directAttributeHints[0] = hint;
                    continue;
                }
                indirectAttributeHints[i-1] = CardAttribute::null;
            }
        }
        else // if color hint
        {
            for (int i = 6; i < 11; i++)
            {
                if (i == int(hint))
                {
                    directAttributeHints[1] = hint;
                    continue;
                }
                indirectAttributeHints[i-1] = CardAttribute::null;
            }
        }
    }
    else // is indirect hint
    {
        indirectAttributeHints[int(hint)-1] = CardAttribute::null;
    }
}


GameSystem::GameSystem(PlayerCount pNumber)// : certaintyAi(Certainty(*this)), omniscientAi(Omniscient(*this)), ruleBasedAi(RuleBased(*this)), hatPrincipleAi(HatPrinciple(*this)) // TMP TO BE DELETED
{
    startGame(pNumber);
}

void GameSystem::startGame(PlayerCount pNumber)
{
    aiType = AITypes::Omniscient;
    playersNumber = pNumber;
    std::random_device rd = std::random_device {};
    std::default_random_engine rng = std::default_random_engine { rd() };
    std::uniform_int_distribution<int> randomStartPlayer(1, int(pNumber));
    drawPile.clear(), discardPile.clear(), logList.clear();
    p0.clear(), p1.clear(), p2.clear(), p3.clear(), p4.clear();
    whiteStack = CardAttribute::null;
    blueStack = CardAttribute::null;
    yellowStack = CardAttribute::null;
    redStack = CardAttribute::null;
    greenStack = CardAttribute::null;
    //wichPlayerTurn = randomStartPlayer(rng);
    turn = 1;
    wichPlayerTurn = 1;
    score = 0;
    hintTokens = 8;
    errorTokens = 0;
    endCountdown = -1;
    setupCards(rng);
    gameEnd = false;
    isInstantAIGame = false;
    time = std::chrono::high_resolution_clock::now();
    timer = time + std::chrono::milliseconds(delay);
}

void GameSystem::startGame(PlayerCount pNumber, AITypes ai)
{
    aiType = ai;
    playersNumber = pNumber;
    std::random_device rd = std::random_device {};
    std::default_random_engine rng = std::default_random_engine { rd() };
    std::uniform_int_distribution<int> randomStartPlayer(1, int(pNumber));
    drawPile.clear(), discardPile.clear(), logList.clear();
    p0.clear(), p1.clear(), p2.clear(), p3.clear(), p4.clear();
    whiteStack = CardAttribute::null;
    blueStack = CardAttribute::null;
    yellowStack = CardAttribute::null;
    redStack = CardAttribute::null;
    greenStack = CardAttribute::null;
    wichPlayerTurn = randomStartPlayer(rng);
    turn = 1;
    score = 0;
    hintTokens = 8;
    errorTokens = 0;
    endCountdown = -1;
    setupCards(rng);
    gameEnd = false;
    isInstantAIGame = false;
    time = std::chrono::high_resolution_clock::now();
    timer = time + std::chrono::milliseconds(delay);
}

int GameSystem::startGame(PlayerCount pNumber, AITypes ai, std::default_random_engine& rng)
{
    aiType = ai;
    isInstantAIGame = true;
    playersNumber = pNumber;
    std::uniform_int_distribution<int> randomStartPlayer(1, int(pNumber));
    drawPile.clear(), discardPile.clear(), logList.clear();
    p0.clear(), p1.clear(), p2.clear(), p3.clear(), p4.clear();
    whiteStack = CardAttribute::null;
    blueStack = CardAttribute::null;
    yellowStack = CardAttribute::null;
    redStack = CardAttribute::null;
    greenStack = CardAttribute::null;
    wichPlayerTurn = randomStartPlayer(rng);
    turn = 1;
    score = 0;
    hintTokens = 8;
    errorTokens = 0;
    endCountdown = -1;
    setupCards(rng);
    gameEnd = false;
    return score;
}

void GameSystem::setupCards(std::default_random_engine& rng)
{
    // Setup base deck, to add to draw pile
    for (int color = 6; color < 11; color++)
    {
        drawPile.push_back(Card(CardAttribute::One, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::One, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::One, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Two, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Two, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Three, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Three, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Four, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Four, CardAttribute(color)));
        drawPile.push_back(Card(CardAttribute::Five, CardAttribute(color)));
    }
    // shuffle draw pile
    std::shuffle(std::begin(drawPile), std::end(drawPile), rng);
    // assigne cards hands to players
    if (playersNumber == PlayerCount::TwoPlayers || playersNumber == PlayerCount::ThreePlayers) // Give 5 cards per players, when 2 or 3 players
    {
        for (int i = 0; i < 5; i++)
        {
            for (int player = 1; player < int(playersNumber)+1; player++)
            {
                switch(Player(player))
                {
                    case Player::P0:
                        p0.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P1:
                        p1.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P2:
                        p2.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P3:
                        p3.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P4:
                        p4.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::null:
                        break;
                }

            }
        }
    }
    else // Otherwise, 4 cards per players, when 4 or 5 players
    {
        for (int i = 0; i < 4; i++)
        {
            for (int player = 1; player < int(playersNumber)+1; player++)
            {
                switch(Player(player))
                {
                    case Player::P0:
                        p0.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P1:
                        p1.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P2:
                        p2.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P3:
                        p3.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::P4:
                        p4.push_back(drawPile.back());
                        drawPile.pop_back();
                        break;
                    case Player::null:
                        break;
                }

            }
        }
    }
}

void GameSystem::gameLoop()
{
    // "gameloop", if player turn, then do nothing and wait for player interaction to play, otherwise wait timer for AI to play
    if (Player(wichPlayerTurn) == Player::P0 || gameEnd)
    {
        return;
    }
    time = std::chrono::high_resolution_clock::now();
    if (time > timer)
    {
        switch(aiType)
        {
            case AITypes::Certainty:
                Certainty::genMove(*this);
                break;
            case AITypes::Omniscient:
                Omniscient::genMove(*this);
                break;
            case AITypes::RuleBased:
                RuleBased::genMove(*this);
                break;
            case AITypes::HatPrinciple:
                HatPrinciple::genMove(*this);
                break;
            case AITypes::null:
                break;
        }
        timer = time + std::chrono::milliseconds(delay);
    }
}

void GameSystem::resetAIDelay()
{
    time = std::chrono::high_resolution_clock::now();
    timer = time + std::chrono::milliseconds(delay);
}

bool GameSystem::isPlayable(Card card)
{
    // Look is card is playable to the stack, if yes then do so and return true, otherwise do nothing and return false
    switch(card.color)
    {
        case CardAttribute::White:
            if (int(whiteStack)+1 == int(card.number))
            {
                whiteStack = CardAttribute(int(whiteStack)+1);
                if (whiteStack == CardAttribute::Five)
                {
                    hintTokens++;
                }
                return true;
            }
            break;
        case CardAttribute::Blue:
            if (int(blueStack)+1 == int(card.number))
            {
                blueStack = CardAttribute(int(blueStack)+1);
                if (blueStack == CardAttribute::Five)
                {
                    hintTokens++;
                }
                return true;
            }
            break;
        case CardAttribute::Yellow:
            if (int(yellowStack)+1 == int(card.number))
            {
                yellowStack = CardAttribute(int(yellowStack)+1);
                if (yellowStack == CardAttribute::Five)
                {
                    hintTokens++;
                }
                return true;
            }
            break;
        case CardAttribute::Red:
            if (int(redStack)+1 == int(card.number))
            {
                redStack = CardAttribute(int(redStack)+1);
                if (redStack == CardAttribute::Five)
                {
                    hintTokens++;
                }
                return true;
            }
            break;
        case CardAttribute::Green:
            if (int(greenStack)+1 == int(card.number))
            {
                greenStack = CardAttribute(int(greenStack)+1);
                if (greenStack == CardAttribute::Five)
                {
                    hintTokens++;
                }
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

void GameSystem::playCard(int cardIndex)
{
    // current player play a card, might go to a color stack, or go to the discard pile while gaining a errorToken
    addLog(true, cardIndex);
    switch(Player(wichPlayerTurn))
    {
        case Player::P0:
            if (!isPlayable(p0[cardIndex]))
            {
                errorTokens++;
                discardPile.push_back(p0[cardIndex]);
            }
            else
            {
                score++;
            }
            p0.erase(p0.begin()+cardIndex);
            drawCard();
            break;
        case Player::P1:
            if (!isPlayable(p1[cardIndex]))
            {
                errorTokens++;
                discardPile.push_back(p1[cardIndex]);
            }
            else
            {
                score++;
            }
            p1.erase(p1.begin()+cardIndex);
            drawCard();
            break;
        case Player::P2:
            if (!isPlayable(p2[cardIndex]))
            {
                errorTokens++;
                discardPile.push_back(p2[cardIndex]);
            }
            else
            {
                score++;
            }
            p2.erase(p2.begin()+cardIndex);
            drawCard();
            break;
        case Player::P3:
            if (!isPlayable(p3[cardIndex]))
            {
                errorTokens++;
                discardPile.push_back(p3[cardIndex]);
            }
            else
            {
                score++;
            }
            p3.erase(p3.begin()+cardIndex);
            drawCard();
            break;
        case Player::P4:
            if (!isPlayable(p4[cardIndex]))
            {
                errorTokens++;
                discardPile.push_back(p4[cardIndex]);
            }
            else
            {
                score++;
            }
            p4.erase(p4.begin()+cardIndex);
            drawCard();
            break;
        case Player::null:
            break;
    }
    nextTurn();
}

void GameSystem::discardCard(int cardIndex)
{
    // current player discard one of his card, gain a hintToken
    addLog(false, cardIndex);
    switch(Player(wichPlayerTurn))
    {
        case Player::P0:
            discardPile.push_back(p0[cardIndex]);
            p0.erase(p0.begin()+cardIndex);
            drawCard();
            break;
        case Player::P1:
            discardPile.push_back(p1[cardIndex]);
            p1.erase(p1.begin()+cardIndex);
            drawCard();
            break;
        case Player::P2:
            discardPile.push_back(p2[cardIndex]);
            p2.erase(p2.begin()+cardIndex);
            drawCard();
            break;
        case Player::P3:
            discardPile.push_back(p3[cardIndex]);
            p3.erase(p3.begin()+cardIndex);
            drawCard();
            break;
        case Player::P4:
            discardPile.push_back(p4[cardIndex]);
            p4.erase(p4.begin()+cardIndex);
            drawCard();
            break;
        case Player::null:
            break;
    }
    hintTokens++;
    nextTurn();
}

void GameSystem::giveHint(CardAttribute hint, Player player)
{
    // a player receive direct hint / indirect hint to all of his cards, at the price of a hintToken
    addLog(int(player), hint);
    switch(player)
    {
        case Player::P0:
            for (int i = 0; i < int(p0.size()); i++)
            {
                if ((p0[i].color == hint) || (p0[i].number == hint))
                {
                    p0[i].addHint(hint, true);
                }
                else
                {
                    p0[i].addHint(hint, false);
                }
            }
            break;
        case Player::P1:
            for (int i = 0; i < int(p1.size()); i++)
            {
                if ((p1[i].color == hint) || (p1[i].number == hint))
                {
                    p1[i].addHint(hint, true);
                }
                else
                {
                    p1[i].addHint(hint, false);
                }
            }
            break;
        case Player::P2:
            for (int i = 0; i < int(p2.size()); i++)
            {
                if ((p2[i].color == hint) || (p2[i].number == hint))
                {
                    p2[i].addHint(hint, true);
                }
                else
                {
                    p2[i].addHint(hint, false);
                }
            }
            break;
        case Player::P3:
            for (int i = 0; i < int(p3.size()); i++)
            {
                if ((p3[i].color == hint) || (p3[i].number == hint))
                {
                    p3[i].addHint(hint, true);
                }
                else
                {
                    p3[i].addHint(hint, false);
                }
            }
            break;
        case Player::P4:
            for (int i = 0; i < int(p4.size()); i++)
            {
                if ((p4[i].color == hint) || (p4[i].number == hint))
                {
                    p4[i].addHint(hint, true);
                }
                else
                {
                    p4[i].addHint(hint, false);
                }
            }
            break;
        case Player::null:
            break;
    }
    hintTokens--;
    nextTurn();
}

void GameSystem::drawCard()
{
    // current player draw card
    if (!drawPile.empty())
    {
        switch(Player(wichPlayerTurn))
        {
            case Player::P0:
                p0.push_back(drawPile.back());
                drawPile.pop_back();
                break;
            case Player::P1:
                p1.push_back(drawPile.back());
                drawPile.pop_back();
                break;
            case Player::P2:
                p2.push_back(drawPile.back());
                drawPile.pop_back();
                break;
            case Player::P3:
                p3.push_back(drawPile.back());
                drawPile.pop_back();
                break;
            case Player::P4:
                p4.push_back(drawPile.back());
                drawPile.pop_back();
                break;
            case Player::null:
                break;
        }
    }
}

void GameSystem::nextTurn()
{
    turn++;
    // if was turn of last player, make it go back to first player
    if (wichPlayerTurn == int(playersNumber))
    {
        wichPlayerTurn = 1;
    }
    // next player turn
    else
    {
        wichPlayerTurn++;
    }
    // if won, then end
    if (score == 25)
    {
        addLog("GAME END| Game has been won !");
        gameEnd = true;
    }
    // if 3 errors, then end
    if (errorTokens == 3)
    {
        addLog("GAME END| 3 errors...");
        gameEnd = true;
    }
    // decrement countdown
    if (endCountdown >= 0)
    {
        endCountdown--;
    }
    // if draw pile empty, start countdown
    if (drawPile.size() == 0 && endCountdown == -1) {
        endCountdown = int(playersNumber);
    }
    // if countdown reached 0, then end
    if (endCountdown == 0)
    {
        addLog("GAME END| No more turns.");
        gameEnd = true;
    }
}

std::string GameSystem::cardToString(Card card)
{
    std::string str;
    switch(card.color)
    {
        case CardAttribute::White:
            str += "[White ";
            break;
        case CardAttribute::Blue:
            str += "[Blue ";
            break;
        case CardAttribute::Yellow:
            str += "[Yellow ";
            break;
        case CardAttribute::Red:
            str += "[Red ";
            break;
        case CardAttribute::Green:
            str += "[Green ";
            break;
        default:
            break;
    }
    switch(card.number)
    {
        case CardAttribute::One:
            str += "1]";
            break;
        case CardAttribute::Two:
            str += "2]";
            break;
        case CardAttribute::Three:
            str += "3]";
            break;
        case CardAttribute::Four:
            str += "4]";
            break;
        case CardAttribute::Five:
            str += "5]";
            break;
        default:
            break;
    }
    return str;
}

std::string GameSystem::playerToString(int player)
{
    switch(player)
    {
        case 1:
            return std::string("Player");
            break;
        default:
            return std::string("#" + std::to_string(player-1));
            break;
    }
}

void GameSystem::addLog(bool play, int index)
{
    std::vector<Card> pCards = getCurrentPlayerCards(*this);
    if (play)
    {
        logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->PLAY " + cardToString(pCards[index]));
    }
    else
    {
        logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->DISCARD " + cardToString(pCards[index]));
    }
}

void GameSystem::addLog(int player, CardAttribute hint)
{
    switch(hint)
    {
        case CardAttribute::One:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [1] to " + playerToString(player));
            break;
        case CardAttribute::Two:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [2] to " + playerToString(player));
            break;
        case CardAttribute::Three:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [3] to " + playerToString(player));
            break;
        case CardAttribute::Four:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [4] to " + playerToString(player));
            break;
        case CardAttribute::Five:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [5] to " + playerToString(player));
            break;
        case CardAttribute::White:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [White] to " + playerToString(player));
            break;
        case CardAttribute::Blue:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [Blue] to " + playerToString(player));
            break;
        case CardAttribute::Yellow:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [Yellow] to " + playerToString(player));
            break;
        case CardAttribute::Red:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [Red] to " + playerToString(player));
            break;
        case CardAttribute::Green:
            logList.push_back(std::to_string(turn) + "| " + playerToString(wichPlayerTurn) + "->HINT [Green] to " + playerToString(player));
            break;
        default:
            break;
    }
}

void GameSystem::addLog(std::string text)
{
    logList.push_back(text);
}

std::vector<Card>& GameSystem::getPlayerCards(int player)
{
    switch(Player(player))
    {
        case Player::P0:
            return p0;
            break;
        case Player::P1:
            return p1;
            break;
        case Player::P2:
            return p2;
            break;
        case Player::P3:
            return p3;
            break;
        case Player::P4:
            return p4;
            break;
        default: // should not happen
            return p0;
            break;
    }
}

CardAttribute GameSystem::getStackByIndex(int index)
{
    switch(index)
    {
        case 0:
            return whiteStack;
            break;
        case 1:
            return blueStack;
            break;
        case 2:
            return yellowStack;
            break;
        case 3:
            return redStack;
            break;
        case 4:
            return greenStack;
            break;
        default:
            return CardAttribute::null;
            break;
    }
}

int GameSystem::getCopyNmbOfCardInDiscard(CardAttribute number, CardAttribute color)
{
    int nmb = 0;
    for (int i = 0; i < int(discardPile.size()); i++)
    {
        if (discardPile[i].number == number &&discardPile[i].color == color)
        {
            nmb++;
        }
    }
    return nmb;
}
