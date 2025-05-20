#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class Card;
class Deck;
enum Color;

class HumanPlayer : public Player {
    public:
        HumanPlayer();
        HumanPlayer(string name);
        Card* playTurn(Card* topCard, Color currentColor, Deck* decks) override;
        // void displayHand();
        Card* selectCard();
        Color selectColor();

};

#endif