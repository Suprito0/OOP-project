#ifndef NUMBERCARD_H
#define NUMBERCARD_H

#include "Card.h"

class NumberCard : public Card
{
private:
  int number;

public:
  NumberCard(Color color, int num);
  int get_Number() const;
  bool canPlayOn(Card *topCard) override;
  void play(Game *game) override;
  std::string toString() override;
  int get_number();
  ActionType get_ActionType();
  string get_ActionTypeString();
};

#endif // NUMBERCARD_H