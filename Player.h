#ifndef PLAYER_H
#define PLAYER_H

#include "Enum.h"
class Card;
class Deck;
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Player
{
protected:
  vector<Card *> hand;
  string name;
  int playerIndex;
  bool isItHuman;
  bool hasCalledUno;

public:
  Player();
  Player(string name);
  virtual Card *playTurn(Card *topCard, Color currentColor, Deck *decks) = 0;
  void addCardToHand(Card *card);
  void removeCardFromHand(Card *card);
  void callUno(bool uno);
  bool getUno();
  size_t getHandSize();
  string getName();
  bool isHuman();
  void displayHand();
  void setIndex(int index);
  int getIndex();
  string toLower(const string &str);
  int calculateScore();
  vector<Card *> getHand();
  Color chooseOptimalColor();
  virtual ~Player();
};

#endif