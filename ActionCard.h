#ifndef ACTIONCARD_H
#define ACTIONCARD_H
#include "Card.h"
enum ActionType{Skip,Reverse,Draw_Two,Wild,Wild_Draw_Four};

class ActionCard: public Card{
protected:
ActionType action;
public:
ActionCard(Color color,ActionType type);
ActionType get_ActionType() const;
bool canPlayOn(Card* topCard) override;
void play(Game* game) override;
std::string toString() override;
};

#endif //ACTIONCARD_H
