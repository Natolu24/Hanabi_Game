#pragma once

#include "gamesystem.hpp"

enum class CardAttribute;
class Card;
class GameSystem;

// players
class Certainty
{
public:
    static void genMove(GameSystem& gameSys);
};

class Omniscient
{
public:
    static void genMove(GameSystem& gameSys);
};

class RuleBased
{
public:
    static void genMove(GameSystem& gameSys);
};

class HatPrinciple
{
public:
    static void genMove(GameSystem& gameSys);
};

// getters
std::vector<Card>& getCurrentPlayerCards(GameSystem& gameSys);
std::array<CardAttribute, 5> getCurrentStackNeedingCard(GameSystem& gameSys);

// helpers
bool isPlayableFromHints(GameSystem& gameSys, Card card);
bool isPlayableFromCard(GameSystem& gameSys, Card card);
bool isDisposableNumberFromHints(Card card, CardAttribute min);
bool isDisposableColorFromHints(GameSystem& gameSys, Card card);
bool isDisposableNumberFromCard(Card card, CardAttribute min);
bool isDisposableColorFromCard(GameSystem& gameSys, Card card);
bool lookIfCardIsUnique(GameSystem& gameSys, Card card);

// actions
bool checkCertainMove(GameSystem& gameSys);
bool giveCoherentHint(GameSystem& gameSys);
bool giveDisposableHint(GameSystem& gameSys);
bool discardDisposableCard(GameSystem& gameSys);
bool discardOldestUnhintedCard(GameSystem& gameSys);

bool tryCheatMove(GameSystem& gameSys);
bool tryCheatDiscardUseless(GameSystem& gameSys);
bool giveRandomHint(GameSystem& gameSys);
bool tryCheatSafeDiscard(GameSystem& gameSys);

bool tryHintIntentionAndPlay(GameSystem& gameSys);
bool tryGiveHintIntention(GameSystem& gameSys);
bool tryDiscardSafe(GameSystem& gameSys);


