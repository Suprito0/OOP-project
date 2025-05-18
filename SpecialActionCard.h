#ifndef SPECIALACTIONCARD_H
#define SPECIALACTIONCARD_H
#include"ActionCard.h"
#include"AIPlayer.h"
#include"Card.h"
#include"Deck.h"
#include"Game.h"
#include"GameMode.h"
#include"HumanPlayer.h"
#include"NumberCard.h"
#include"Player.h"

class SpecialActionCard : public ActionCard {
 private:
  ActionType selectedAction;

 public:
  SpecialActionCard(Color color);
  void randAction();
  ActionType get_SelectedAction() const;
  void play(Game* game) override;
  std::string toString() override;
  ActionType get_ActionType();
};

#endif  // SPECIALACTIONCARD_H
