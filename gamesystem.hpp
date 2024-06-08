#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <vector>
#include "players.hpp"

enum class PlayerCount { P2 = 2, P3, P4, P5 };
enum class AITypes { Certainty, Omniscient, RuleBased, HatPrinciple };
enum class cardAttribute { One, Two, Three, Four, Five, White, Blue, Yellow, Red, Green };

class Card
{
public:
    cardAttribute number;
    cardAttribute color;
    std::array<cardAttribute, 5> directAttributeHints;
    std::array<cardAttribute, 10> indirectAttributeHints = {cardAttribute::One, cardAttribute::Two, cardAttribute::Three, cardAttribute::Four, cardAttribute::Five,
                                                            cardAttribute::White, cardAttribute::Blue, cardAttribute::Yellow, cardAttribute::Red, cardAttribute::Green };
    void addHint(cardAttribute attribute, bool isDirectHint);
};

class GameSystem
{
public:
    PlayerCount playersNumber;
    int wichPlayerTurn, score, hintTokens, errorTokens;
    std::vector<Card> drawPile, discardPile;
    std::vector<std::string> logList;
    std::vector<Card> p0;
    std::vector<Card> p1;
    std::vector<Card> p2;
    std::vector<Card> p3;
    std::vector<Card> p4;
    void startGame();
    void gameLoop();
    void setupCards();
    void addLog(); // ajouter sa à "GameClass"
};

