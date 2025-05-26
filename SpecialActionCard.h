#ifndef SPECIALACTIONCARD_H
#define SPECIALACTIONCARD_H

#include "ActionCard.h"

class SpecialActionCard : public ActionCard
{
private:
  int targetPlayerIndex;

public:
  SpecialActionCard(Color color, ActionType type);
  void play(Game *game) override;
  string toString() override;
  int get_TargetPlayerIndex() override;
  void specialAction(Game *game) override;
};

#endif // SPECIALACTIONCARD_H