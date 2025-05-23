#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class Game;
class Card;
class Deck;
enum Color;

class HumanPlayer : public Player
{
private:
Game* gameRef = nullptr;
public:
    HumanPlayer();
    HumanPlayer(string name);
    Card *playTurn(Card *topCard, Color currentColor, Deck *decks) override;
    // void displayHand();
    Card *selectCard();
    Color selectColor();
    void setGame(Game* g);
    bool hasValidMove(Game* game) const;
};

#endif