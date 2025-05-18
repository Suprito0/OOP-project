#ifndef AIPLAYER_H
#define AIPLAYER_H

#include"ActionCard.h"
#include"Card.h"
#include"Deck.h"
#include"Game.h"
#include"GameMode.h"
#include"HumanPlayer.h"
#include"NumberCard.h"
#include"Player.h"
#include"SpecialActionCard.h"

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