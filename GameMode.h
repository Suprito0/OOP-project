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
  string modeName;
  int numOfPlayers;
  bool isFast;

public:
  GameMode();
  GameMode(string modeName);
  void initialize();
  string getModeName();
  bool getIsFast();
  void setIsFast(bool turn);
  int getNumOfPlayers();
};

#endif