#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include"ActionCard.h"
#include"AIPlayer.h"
#include"Card.h"
#include"Deck.h"
#include"Game.h"
#include"GameMode.h"
#include"NumberCard.h"
#include"Player.h"
#include"SpecialActionCard.h"

class HumanPlayer : public Player {
    public:
        HumanPlayer();
        HumanPlayer(string name);
        Card* playTurn(Card* topCard, Color currentColor, Deck* decks) override;
        void displayHand();
        Card* selectCard();
        Color selectColor();

};

#endif