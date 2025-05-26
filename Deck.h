#ifndef DECK_H
#define DECK_H

class Card;
class Game;
#include <vector>

#include "Enum.h"
using std::vector;

class Deck
{
private:
  vector<Card *> drawPile;
  vector<Card *> discardPile;

public:
  Deck(Game *game);
  void initialize(Game *game);
  void shuffle();
  Card *drawCard();
  void addToDiscardPile(Card *card);
  Card *get_TopDiscard() const;
  void reshuffleIfNeeded();
  bool isInList(vector<Card *> &list, Card *card);
  ~Deck();
};

#endif // DECK_H