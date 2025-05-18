#ifndef AIPLAYER_H
#define AIPLAYER_H

#include"Player.h"
class Deck;
class Card;
enum Color;

class AIPlayer : public Player {
    public:
        AIPlayer();
        AIPlayer(string name);
        Card* playTurn(Card* topCard, Color currentColor, Deck* decks) override;
        Card* strategicCardSelection();
        Color chooseOptimalColor();
        int get_number();
};

#endif