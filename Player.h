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
  vector<Card *> hand; // stores the cards which are dealt to the player
  string name; // name of the player
  int playerIndex; // index of the player in the vector stored on the Game object
  bool isItHuman; // indicates if it is human
  bool hasCalledUno; // indicates if it has called uno

public:
  Player();//default constructor
  Player(string name);//constructor
  virtual Card *playTurn(Card *topCard, Color currentColor, Deck *decks) = 0; // Player plays their turn
  void addCardToHand(Card *card);//add card from drawPile to hand
  void removeCardFromHand(Card *card);// removes card from hand and puts it in the discard pile
  void callUno(bool uno); // sets hasCalledUno
  bool getUno(); // checks if the player has called uno
  size_t getHandSize();//returns the size of the hand
  string getName();//returns the name of the player
  bool isHuman();//checks if player is human or AI
  void displayHand();//displays the player's hand on the terminal
  void setIndex(int index);// sets the index of the player
  int getIndex(); // returns the index of the player
  string toLower(const string &str); // converts string to lower case
  int calculateScore(); // calculates the player's score
  vector<Card *> getHand(); // returns the player's hand
  Color chooseOptimalColor(); // chooses a color based on the hand
  virtual ~Player();//destructor
};

#endif