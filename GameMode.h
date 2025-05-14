#ifndef GAMEMODE_H
#define GAMEMODE_H

//include libraries
#include<iostream>
#include<string.h>
#include<vector> 
#include"Card.h" 
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
        int calculateScore(vector<Card*> remainingCards);
        string getDescription();
};

#endif