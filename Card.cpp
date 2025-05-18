#include "Card.h"
#include "Game.h"

Card::Card(Color color, CardType type) {
  this->color = color;
  this->type = type;
}

Card::Card() {
  color = None;
  type = Number;
}

Color Card::get_Color() const { return color; }

CardType Card::get_CardType() const { return type; }

void Card::set_Color(Color newColor) { color = newColor; }

Card::~Card() {}