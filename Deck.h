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
  Deck(Game *game);                                // Constructor
  void initialize(Game *game);                     // populates the drawPile with cards
  void shuffle();                                  // shuffles the draw pile
  Card *drawCard();                                // draws a card from the drawpile
  void addToDiscardPile(Card *card);               // adds a card to the discard pile
  Card *get_TopDiscard() const;                    // gets the most recent played card
  void reshuffleIfNeeded();                        // moves the discard pile to the draw pile and reshuffles it
  bool isInList(vector<Card *> &list, Card *card); // checks if a pointer to a card object is already deleted or not
  ~Deck();
};

#endif // DECK_H