#pragma once

#include "gamesystem.hpp"

class GameSystem;

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




