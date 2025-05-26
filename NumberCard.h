#ifndef NUMBERCARD_H
#define NUMBERCARD_H

#include "Card.h"

class NumberCard : public Card
{
private:
  int number;

public:
  NumberCard(Color color, int num);
  bool canPlayOn(Card *topCard) override;
  void play(Game *game) override;
  string toString() override;
  int get_number() override;
  ActionType get_ActionType() override;
  string get_ActionTypeString() override;
};

#endif // NUMBERCARD_H