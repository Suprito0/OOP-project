#ifndef DECK_H
#define DECK_H

#include"ActionCard.h"
#include"AIPlayer.h"
#include"Card.h"
#include"Game.h"
#include"GameMode.h"
#include"HumanPlayer.h"
#include"NumberCard.h"
#include"Player.h"
#include"SpecialActionCard.h"
#include <vector>

class Deck {
 private:
  vector<Card*> cards;
  vector<Card*> discardPile;

 public:
  Deck();
  void initialize();
  void shuffle();
  Card* drawCard();
  void addToDiscardPile(Card* card);
  Card* get_TopDiscard() const;
  vector<Card*> get_cards();
  vector<Card*> get_discardPile();
  void reshuffleIfNeeded();
  int get_DeckSize() const;
  int get_DiscardSize() const;
  ~Deck();
};

#endif  // DECK_H