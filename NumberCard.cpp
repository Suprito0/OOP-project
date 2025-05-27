#include "NumberCard.h"

#include <iostream>

#include "Game.h"

// Constructor: sets the card's color and number
NumberCard::NumberCard(Color color, int num) : Card(color, Number)
{
  this->number = num;
}

// Implement the canPlayOn method (checks if the top card matches the number or
// color)
bool NumberCard::canPlayOn(Card *topCard)
{
  if (topCard == nullptr)
  {
    return true; // If no top card, you can play any card
  }
  // Check if the top card is a NumberCard
  if (topCard->get_CardType() == Number)
  {
    // Compare number or color directly
    NumberCard *topNumberCard = dynamic_cast<NumberCard *>(topCard);
    return topNumberCard && (topNumberCard->get_number() == number ||
                             topNumberCard->get_Color() == color);
  }

  // If the top card is an action or special card, you can play based on color
  return topCard->get_Color() == color;
}

// Called when the card is played
void NumberCard::play(Game *game)
{
  // Implement the logic to handle the effect of the card being played
  cout << "Played Number Card: " << toString() << endl;
  game->changeColor(this->color);
  game->isFirstTurn();
}

// Converts this card into a readable string like "Red 7"
string NumberCard::toString()
{
  string colorStr;
  switch (color)
  {
  case Red:
    colorStr = "Red";
    break;
  case Green:
    colorStr = "Green";
    break;
  case Blue:
    colorStr = "Blue";
    break;
  case Yellow:
    colorStr = "Yellow";
    break;
  default:
    colorStr = "None";
    break;
  }

  return colorStr + " " + to_string(number);
}

// Returns the number value of the card (e.g. 3, 7)
int NumberCard::get_number() { return this->number; }

// Not really used for NumberCard, but implemented to satisfy interface
// Returns a dummy ActionType value (Wild) — should be ignored
ActionType NumberCard::get_ActionType() { return Wild; }

// Returns the number as a string — used for display or compatibility
string NumberCard::get_ActionTypeString()
{
  return to_string(this->get_number());
}