#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player {
    public:
        Card* playTurn(Card* topCard, Color currentColor, Deck* draw, Deck* discard);
        Card* strategicCardSelection();
        Color chooseOptimalColor();

};

#endif