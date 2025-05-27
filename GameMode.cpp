#include "GameMode.h"

#include "Card.h"
// constructor sets ifFast, modeName and runs the initialize function
GameMode::GameMode()
{
  this->isFast = false;
  this->modeName = "normal";
  this->initialize();
}
GameMode::GameMode(string modeName)
{
  this->isFast = false;
  this->modeName = modeName;
  this->initialize();
}

// sets the numOfPlayers according to the modeName
void GameMode::initialize()
{
  if (modeName == "normal")
  {
    this->numOfPlayers = 1;
    cout << "Single-Player Mode selected.\n";
  }
  else if (modeName == "multiplayer")
  {
    string inputString;
    while (true)
    {
      cout << "How many human players will be playing? (1-4)" << endl;
      cin >> inputString;
      try
      {
        this->numOfPlayers = stoi(inputString);
        if (this->numOfPlayers >= 1 && this->numOfPlayers <= 4)
        {
          cout << (numOfPlayers == 1 ? "\nSingle-Player Mode selected.\n"
                                     : "\nMulti-Player Mode selected.\n");
          break;
        }
        else
        {
          cout << "Invalid input. Please choose a number between 1 & 4."
               << endl;
          continue;
        }
      }
      catch (const exception &e)
      {
        cout << "Invalid input. Please enter a number." << endl;
        continue;
      }
    }
  }
  else if (modeName == "simulation")
  {
    this->numOfPlayers = 0;
  }
  else
  {
    cout << "invalid Gamemode" << endl;
  }
}

string GameMode::getModeName() { return this->modeName; }

int GameMode::getNumOfPlayers() { return this->numOfPlayers; }

bool GameMode::getIsFast() { return this->isFast; }

void GameMode::setIsFast(bool turn) { this->isFast = turn; }