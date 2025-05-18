#ifndef ACTIONCARD_H
#define ACTIONCARD_H

#include"AIPlayer.h"
#include"Card.h"
#include"Deck.h"
#include"Game.h"
#include"GameMode.h"
#include"HumanPlayer.h"
#include"NumberCard.h"
#include"Player.h"
#include"SpecialActionCard.h"

class ActionCard : public Card {
 protected:
  ActionType action;

 public:
  ActionCard(Color color, ActionType type);
  ActionType get_ActionType() const;
  bool canPlayOn(Card* topCard) override;
  void play(Game* game) override;
  std::string toString() override;
  int get_number();
  ActionType get_ActionType();
};

#endif  // ACTIONCARD_H
