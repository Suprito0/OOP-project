#ifndef GAMEMODE_H
#define GAMEMODE_H

//include libraries
#include<iostream>
#include<string>
#include <vector>
class Card;


using namespace std;

class GameMode{
    protected:
        string modeName, gameModeDescription;
        int winningScore;
        bool allowStacking;
    public:
        GameMode();
        GameMode(string modeName);
        void initialize();
        size_t calculateScore(vector<Card*> remainingCards);
        string getDescription();
        string getModeName();
        int getWinningScore();
        void getAllowStacking();
};

#endif