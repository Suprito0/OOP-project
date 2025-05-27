#ifndef GAMEMODE_H
#define GAMEMODE_H

// include libraries
#include <iostream>
#include <string>
#include <vector>

#include "Enum.h"
class Card;

using namespace std;

class GameMode
{
protected:
  string modeName;  // Stores name of Mode
  int numOfPlayers; // Stores number of human player
  bool isFast;      // If fast mode is on or not

public:
  GameMode();                // default constructor
  GameMode(string modeName); // constructor
  void initialize();         // initializes the object according to its name
  string getModeName();      // returns modeName
  bool getIsFast();          // returns isFast
  void setIsFast(bool turn); // sets isFast
  int getNumOfPlayers();     // returns NumOfPlayers
};

#endif