#include "GameMode.h"

#include "Card.h"

GameMode::GameMode() {
  this->isFast = false;
  this->modeName = "normal";
  this->initialize();
}
GameMode::GameMode(string modeName) {
  this->isFast = false;
  this->modeName = modeName;
  this->initialize();
}
void GameMode::initialize() {
  if (modeName == "normal") {
    this->allowStacking = false;
    this->gameModeDescription = "Normal Uno rules with no stacking";
    this->numOfPlayers = 1;
    cout << "Single-Player Mode selected.\n";
  } else if (modeName == "multiplayer") {
    this->allowStacking = false;
    this->gameModeDescription = "Normal Uno with multiple human player.";
    string inputString;
    while (true) {
      cout << "How many human players will be playing? (1-4)" << endl;
      cin >> inputString;
      try {
        this->numOfPlayers = stoi(inputString);
        if (this->numOfPlayers >= 1 && this->numOfPlayers <= 4) {
          cout << (numOfPlayers == 1 ? "\nSingle-Player Mode selected.\n"
                                     : "\nMulti-Player Mode selected.\n");
          break;
        } else {
          cout << "Invalid input. Please choose a number between 1 & 4."
               << endl;
          continue;
        }
      } catch (const std::exception &e) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        continue;
      }
    }
  } else if (modeName == "simulation") {
    this->allowStacking = false;
    this->gameModeDescription = "simulation";
    this->numOfPlayers = 0;
  } else {
    cout << "invalid Gamemode" << endl;
  }
}

string GameMode::getDescription() { return this->gameModeDescription; }

string GameMode::getModeName() { return this->modeName; }

void GameMode::getAllowStacking() {
  if (this->allowStacking == false) {
    cout << "stacking is not allowed" << endl;
  } else {
    cout << "stacking is allowed" << endl;
  }
}
int GameMode::getNumOfPlayers() { return this->numOfPlayers; }

bool GameMode::getIsFast() { return this->isFast; }
void GameMode::setIsFast(bool turn) { this->isFast = turn; }