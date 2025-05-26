#ifndef GAMEMODE_H
#define GAMEMODE_H

// include libraries
#include <iostream>
#include <string>
#include <vector>
#include "Enum.h"
class Card;

using namespace std;

class GameMode
{
protected:
    string modeName, gameModeDescription;
    int winningScore;
    bool allowStacking;
    int numOfPlayers;
    bool isFast;

public:
    GameMode();
    GameMode(string modeName);
    void initialize();
    // size_t calculateScore(vector<Card *> remainingCards);
    string getDescription();
    string getModeName();
    int getWinningScore();
    void getAllowStacking();
    bool getIsFast();

    void setIsFast();

    int getNumOfPlayers();
};

#endif