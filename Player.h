#ifndef PLAYER_H
#define PLAYER_H

class Card;
class Deck;
enum Color;  
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Player {
    protected:
        vector<Card*> hand;
        string name;
        bool hasCalledUno;

    public:
        Player();
        Player(string name);
        virtual Card* playTurn(Card* topCard, Color currentColor, Deck* decks) = 0;
        void addCardToHand(Card* card);
        void removeCardFromHand(Card* card);
        bool hasValidMove(Card* topCard, Color currentColor);
        void callUno();
        size_t getHandSize();
        string getName();
};

#endif