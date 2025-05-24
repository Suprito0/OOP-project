#ifndef SPECIALACTIONCARD_H
#define SPECIALACTIONCARD_H

#include "ActionCard.h"

class SpecialActionCard : public ActionCard
{
private:
  int targetPlayerIndex;

public:
  SpecialActionCard(Color color, ActionType type);
  void randAction();
  ActionType get_SelectedAction() const;
  void play(Game *game) override;
  std::string toString() override;
  string get_CardTypeString() override;
  int get_TargetPlayerIndex() override;
  void specialAction(Game *game) override;

};

#endif // SPECIALACTIONCARD_H
