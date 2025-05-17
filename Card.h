#ifndef CARD_H
#define CARD_H
#include <string>

#include "Game.h"

enum Color { Red, Green, Blue, Yellow, None };
enum CardType { Number, Action, Special_Action };

class Card {
 protected:
  Color color;
  CardType type;

 public:
  Card(Color color, CardType type);
  Card();
  Color get_Color() const;
  CardType get_CardType() const;
  void set_Color(Color newColor);
  virtual bool canPlayOn(Card* topCard) = 0;
  virtual void play(Game* game) = 0;
  virtual std::string toString() = 0;
  // virtual int get_number() = 0;
  virtual ~Card();
};

#endif  // CARD_H