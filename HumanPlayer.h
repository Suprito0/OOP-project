#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
    public:
        Card* playTurn(Card* topCard, Color currentColor) override;
        void displayHand();
        Card* selectCard();
        Color selectColor();

};

#endif