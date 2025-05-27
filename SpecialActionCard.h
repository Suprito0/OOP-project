#ifndef SPECIALACTIONCARD_H
#define SPECIALACTIONCARD_H

#include "ActionCard.h"

class SpecialActionCard : public ActionCard
{
private:
  int targetPlayerIndex; // Index of the player being targetted

public:
  SpecialActionCard(Color color, ActionType type);
  void play(Game *game) override;
  string toString() override;
  int get_TargetPlayerIndex() override;
  void specialAction(Game *game) override; // plays on the targetted player
};

#endif // SPECIALACTIONCARD_H