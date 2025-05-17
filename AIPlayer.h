#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player {
    public:
        AIPlayer();
        AIPlayer(string name);
        Card* playTurn(Card* topCard, Color currentColor, Deck* decks);
        Card* strategicCardSelection();
        Color chooseOptimalColor();
        int get_number();
};

#endif