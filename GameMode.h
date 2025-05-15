#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string.h>

#include <iostream>
#include <vector>

#include "Card.h"
using namespace std;

class GameMode {
 protected:
  string modeName, gameModeDescription;
  int winningScore;
  bool allowStacking;

 public:
  GameMode();
  GameMode(string modeName);
  void initialize();
  size_t calculateScore(vector<Card*> remainingCards);
  string getDescription();
  string getModeName();
  int getWinningScore();
  void getAllowStacking();
};

#endif  // GAMEMODE_H