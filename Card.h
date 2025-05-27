#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
using namespace std;

#include "Enum.h"
class Game;

class Card
{
protected:
  Color color;
  CardType type;

public:
  Card(Color color, CardType type);
  Card();
  Color get_Color() const;
  CardType get_CardType() const;
  string get_ColorString();                  // returns the color of a card in string
  virtual bool canPlayOn(Card *topCard) = 0; // checks if a card if valid to play on the top card
  virtual void play(Game *game) = 0;         // plays the card
  virtual string toString() = 0;             // returns info. about the card in string
  virtual int get_number() = 0;
  virtual ActionType get_ActionType() = 0;
  virtual string get_ActionTypeString() = 0;
  virtual void specialAction(Game *game);
  virtual int get_TargetPlayerIndex();
  virtual ~Card();
};

#endif // CARD_H