#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "players.hpp"

enum class PlayerCount { null, TwoPlayers = 2, ThreePlayers, FourPlayers, FivePlayers };
enum class AITypes { null, Certainty, Omniscient, RuleBased, HatPrinciple };
enum class Player { null, P0, P1, P2, P3, P4 };
enum class CardAttribute { null, One, Two, Three, Four, Five, White, Blue, Yellow, Red, Green };

class Card
{
public:
    CardAttribute number;
    CardAttribute color;
    std::array<CardAttribute, 10> indirectAttributeHints = {CardAttribute::One, CardAttribute::Two, CardAttribute::Three, CardAttribute::Four, CardAttribute::Five,
                                                            CardAttribute::White, CardAttribute::Blue, CardAttribute::Yellow, CardAttribute::Red, CardAttribute::Green };
    Card(CardAttribute number, CardAttribute color);
    void addHint(CardAttribute attribute, bool isDirectHint);
};

class GameSystem
{
public:
    PlayerCount playersNumber;
    AITypes aiType = AITypes::null;
    int wichPlayerTurn, score, hintTokens, errorTokens, endCountdown = -1;
    bool gameEnd, isInstantAIGame = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> time, timer;
    int delay = 1000;
    std::vector<Card> drawPile, discardPile;
    std::vector<std::string> logList; // ajouter sa à "GameScene"
    std::vector<Card> p0;
    std::vector<Card> p1;
    std::vector<Card> p2;
    std::vector<Card> p3;
    std::vector<Card> p4;
    CardAttribute whiteStack = CardAttribute::null;
    CardAttribute blueStack = CardAttribute::null;
    CardAttribute yellowStack = CardAttribute::null;
    CardAttribute redStack = CardAttribute::null;
    CardAttribute greenStack = CardAttribute::null;
    GameSystem(PlayerCount pNumber); // TMP TO BE DELETED
    void startGame(PlayerCount pNumber); // for Player + AIs game
    void startGame(PlayerCount pNumber, AITypes ai); // for AIs only game
    int startGame(PlayerCount pNumber, AITypes ai, std::default_random_engine& rng); // for instant AIs only seeded game with returning score
    void setupCards(std::default_random_engine& rng);
    void gameLoop();
    bool isPlayable(Card card);
    void playCard(int cardIndex);
    void discardCard(int cardIndex);
    void giveHint(CardAttribute hint, Player player);
    void drawCard();
    void nextTurn();
    void addLog(); // ajouter sa à "GameScene"
};

