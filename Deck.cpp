#include "Deck.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"

Deck::Deck(Game *game)
{
  srand(time(0)); // Seed the random generator once in constructor
  initialize(game);
}

void Deck::initialize(Game *game)
{
  drawPile.clear();
  discardPile.clear();
  // UNO standard colors
  vector<Color> colors = {Red, Green, Blue, Yellow};
  // 1. Number Cards (0-9)
  // for (Color color : colors) : range-based for loop
  for (Color color : colors)
  {
    // One 0 per color
    drawPile.push_back(new NumberCard(color, 0));

    // Two of each 1-9 per color
    for (int i = 1; i <= 9; ++i)
    {
      drawPile.push_back(new NumberCard(color, i));
      drawPile.push_back(new NumberCard(color, i));
    }
  }
  // 2. Action Cards (Skip, Reverse, Draw Two)
  for (Color color : colors)
  {
    for (int i = 0; i < 2; ++i)
    {
      drawPile.push_back(new ActionCard(color, Skip));
      drawPile.push_back(new ActionCard(color, Reverse));
      drawPile.push_back(new ActionCard(color, Draw_Two));
    }
  }
  // 3. Wild Cards
  for (int i = 0; i < 4; ++i)
  {
    drawPile.push_back(new ActionCard(None, Wild));           // Wild
    drawPile.push_back(new ActionCard(None, Wild_Draw_Four)); // Wild Draw Four
  }
  // 4. SpecialActionCard
  for (Color color : colors)
  {
    for (int i = 0; i < 1; ++i)
    {
      game->setSpecialCards(new SpecialActionCard(color, Skip));
      game->setSpecialCards(new SpecialActionCard(color, Reverse));
      game->setSpecialCards(new SpecialActionCard(
          color, Draw_Two)); // Adding their address to the Game class
    }
  }

  // Adding the SpecialActionCard set from Game class to the draw deck
  drawPile.insert(drawPile.end(), game->getSpecialCards()->begin(),
                  game->getSpecialCards()->end());

  shuffle();
}

void Deck::shuffle()
{
  for (size_t i = 0; i < drawPile.size(); ++i)
  {
    int j = i + rand() % (drawPile.size() - i); // random index between i and end
    swap(drawPile[i], drawPile[j]);             // swap elements
  }
}

Card *Deck::drawCard()
{
  if (drawPile.empty())
  {
    reshuffleIfNeeded(); // Refill the deck from discard pile
  }

  // check after reshuffling attempt
  if (drawPile.empty())
  {
    cout << "No cards left to draw!" << endl;
    return nullptr;
  }

  Card *top = drawPile.back();
  drawPile.pop_back();
  return top;
}

void Deck::addToDiscardPile(Card *card) { discardPile.push_back(card); }

Card *Deck::get_TopDiscard() const
{
  if (discardPile.empty())
    return nullptr;
  return discardPile.back();
}

void Deck::reshuffleIfNeeded()
{
  if (drawPile.empty() && discardPile.size() > 1)
  {
    Card *top = discardPile.back(); // Keep top discard
    discardPile.pop_back();         // Remove it temporarily

    // Move rest of discard pile back to deck
    drawPile = discardPile;
    discardPile.clear();
    discardPile.push_back(top); // Keep top card on discard pile

    shuffle();
    cout << "Deck reshuffled from discard pile." << endl;
  }
}

bool Deck::isInList(vector<Card *> &deletedCards, Card *card)
{
  for (Card *c : deletedCards)
  {
    if (c == card)
      return true;
  }
  return false;
}

Deck::~Deck()
{

  vector<Card *> deletedCards;

  // Go through draw pile
  for (Card *card : this->drawPile)
  {
    if (!isInList(deletedCards, card))
    {
      deletedCards.push_back(card);
      delete card;
    }
  }
  this->drawPile.clear();

  // Go through discard pile
  for (Card *card : this->discardPile)
  {
    if (!isInList(deletedCards, card))
    {
      deletedCards.push_back(card);
      delete card;
    }
  }
  this->discardPile.clear();
  deletedCards.clear();
}
