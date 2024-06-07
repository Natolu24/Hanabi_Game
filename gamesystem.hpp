#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <vector>
#include <list>
#include "players.hpp"

enum class PlayerCount { P2 = 2, P3, P4, P5 };
enum class cardAttribute { One, Two, Three, Four, Five, White, Blue, Yellow, Red, Green };

class Card
{
    cardAttribute number;
    cardAttribute color;
    std::array<cardAttribute, 5> directAttributeHints;
    std::array<cardAttribute, 10> indirectAttributeHints = {cardAttribute::One, cardAttribute::Two, cardAttribute::Three, cardAttribute::Four, cardAttribute::Five,
                                                            cardAttribute::White, cardAttribute::Blue, cardAttribute::Yellow, cardAttribute::Red, cardAttribute::Green };
public:
    void addHint(cardAttribute attribute, bool isDirectHint);
};

class GameSystem
{
    PlayerCount playersNumber;
    int wichPlayerTurn, score, hintTokens, errorTokens;
    std::vector<Card> drawPile, discardPile;
    std::list<std::string> logList;
public:
    void startGame();
    void gameLoop();
    void setupCards();
    void addLog();
};

