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
  Game *gameRef = nullptr; // Stores the pointer to the game being played by the player

public:
  HumanPlayer();            // Default constructor
  HumanPlayer(string name); // Constructor
  Card *playTurn(Card *topCard, Color currentColor, Deck *decks) override;
  void setGame(Game *game);            // sets the gameRef pointer
  bool hasValidMove(Game *game) const; // checks if the player has any valid move
};

#endif