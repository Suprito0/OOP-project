#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
 private:
  std::vector<Card*> cards;
  std::vector<Card*> discardPile;

 public:
  Deck();
  void initialize();
  void shuffle();
  Card* drawCard();
  void addToDiscardPile(Card* card);
  Card* get_TopDiscard() const;
  void reshuffleIfNeeded();
  int get_DeckSize() const;
  int get_DiscardSize() const;
  ~Deck();
};

#endif  // DECK_H