#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include "Card.h"

class ActionCard : public Card
{
protected:
  ActionType action;

public:
  ActionCard(Color color, ActionType type);
  ActionType get_ActionType() const;
  bool canPlayOn(Card *topCard) override;
  void play(Game *game) override;
  std::string toString() override;
  int get_number();
  ActionType get_ActionType();
  string get_ActionTypeString();
};

#endif // ACTIONCARD_H
