#include "Card.h"

#include "Game.h"

// Constructor with parameters: sets the color and type of the card
Card::Card(Color color, CardType type)
{
  this->color = color;
  this->type = type;
}

// Default constructor: sets color to None and type to Number by default
Card::Card()
{
  color = None;
  type = Number;
}

// Getter for the color of the card
Color Card::get_Color() const { return color; }

// Getter for the type of the card (Number, Action, or Special_Action)
CardType Card::get_CardType() const { return type; }

// Returns the color of the card as a string (e.g., "Red", "Green", etc.)
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

// Placeholder for getting a target player index.
// Most card types don’t use this, so return -1 by default.
int Card::get_TargetPlayerIndex() { return -1; }

// Placeholder for special actions (e.g., targeting a player).
// Only overridden by derived classes like SpecialActionCard.
void Card::specialAction(Game * /*game*/, bool /*willskip*/) {}

// Virtual destructor to ensure proper cleanup when deleting derived card objects through base pointers
Card::~Card() {}