#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
class Deck;
class Card;
enum Color;

class AIPlayer : public Player
{
public:
    AIPlayer();            // default constructor
    AIPlayer(string name); // constructor
    Card *playTurn(Card *topCard, Color currentColor, Deck *decks) override;
    Card *strategicCardSelection(Card *topCard, Color currentColor); // selects a card to play
};

#endif