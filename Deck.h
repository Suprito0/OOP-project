#ifndef DECK_H
#define DECK_H

class Card;
class Game;
#include "Enum.h"
#include <vector>
using std::vector;

class Deck
{
private:
  vector<Card *> cards;
  vector<Card *> discardPile;

public:
  Deck(Game* game);
  void initialize(Game* game);
  void shuffle();
  Card *drawCard();
  void addToDiscardPile(Card *card);
  Card *get_TopDiscard() const;
  vector<Card *> get_cards();
  vector<Card *> get_discardPile();
  void reshuffleIfNeeded();
  int get_DeckSize() const;
  int get_DiscardSize() const;
  ~Deck();
};

#endif // DECK_H