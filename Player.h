#ifndef PLAYER_H
#define PLAYER_H

#include"Enum.h"
class Card;
class Deck;
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Player {
    protected:
        vector<Card*> hand;
        string name;
        bool isItHuman;  
        bool hasCalledUno;

    public:
        Player();
        Player(string name);
        virtual Card* playTurn(Card* topCard, Color currentColor, Deck* decks) = 0;
        void addCardToHand(Card* card);
        void removeCardFromHand(Card* card);
        bool hasValidMove(Card* topCard, Color currentColor);
        void callUno(bool uno);
        bool getUno();
        size_t getHandSize();
        string getName();
        bool isHuman();
        void displayHand();

        Color chooseOptimalColor();
};

#endif