#include "Card.h"
#include "Game.h"

Card::Card(Color color, CardType type)
{
  this->color = color;
  this->type = type;
}

Card::Card()
{
  color = None;
  type = Number;
}

Color Card::get_Color() const { return color; }

CardType Card::get_CardType() const { return type; }

string Card::get_ColorString()
{
  switch (color)
  {
  case Red:
    return "Red ";
  case Green:
    return "Green ";
  case Blue:
    return "Blue ";
  case Yellow:
    return "Yellow ";
  case None:
    return "";
  default:
    return "Unknown ";
  }
}

int Card::get_TargetPlayerIndex() { return -1; }

// string Card::get_CardTypeString()
// {
//   switch (type)
//   {
//   case Number:
//     return to_string(this->get_number());
//   case Action:
//     return this->get_ActionTypeString();
//   case Special_Action:
//     return "Special Action";
//   default:
//     return "Unknown";
//   }
// }

void Card::set_Color(Color newColor) { color = newColor; }

void Card::specialAction(Game *game) {}

Card::~Card() {}