#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include "Card.h"

class ActionCard : public Card {
 protected:
  ActionType action;

 public:
  ActionCard(Color color, ActionType type);
  bool canPlayOn(Card *topCard) override;
  void play(Game *game) override;
  std::string toString() override;
  int get_number() override;
  ActionType get_ActionType() override;
  string get_ActionTypeString() override;
  string get_CardTypeString() override;
};

#endif  // ACTIONCARD_H