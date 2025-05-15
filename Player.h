#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"

#include <vector>

class Player {
 protected:
  std::vector<Card*> hand;
  std::string name;
  bool hasCalledUno;

 public:
  virtual Card* playTurn(Card* topCard, Color currentColor) = 0;
  void addCardToHand(Card* card);
  void removeCardFromHand(Card* card);
  bool hasValidMove(Card* topCard, Color currentColor);
  void callUno();
  size_t getHandSize();
};

#endif