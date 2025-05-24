#include <iostream>

#include "AIPlayer.h"
#include "Deck.h"
#include "Game.h"
#include "GameMode.h"
#include "HumanPlayer.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"
using namespace std;

// Flags and data to track game status
bool gameStarted = false;
bool gameOver = false;
string winnerName = "";
Game* currentGame = nullptr;

void showRules() {
  cout << "\n===== UNO RULES =====\n";
  cout << "1. Each player starts with 7 cards.\n";
  cout << "2. The objective is to be the first player to get rid of all cards.\n";
  cout << "3. On your turn, match the top card by number, color, or action.\n";
  cout << "   Wild and Wild Draw Four cards can be played at any time.\n";
  cout << "4. If you can't play, draw a card.\n";
  cout << "5. Action cards:\n";
  cout << "   - Skip: Next player loses a turn\n";
  cout << "   - Reverse: Reverses direction\n";
  cout << "   - Draw Two: Next player draws 2 cards and skips turn\n";
  cout << "   - Wild: You choose the next color\n";
  cout << "   - Wild Draw Four: Choose a color and next player draws 4 + skips\n";
  cout << "6. Special Action card (your custom rule):\n";
  cout << "   - Choose an action card and target a player of your choice\n";
  cout << "7. UNO rule: Type 0 BEFORE playing your last card to call UNO.\n\n";
}

void showPlayerInfo(const string& playerName) {
  cout << "\n===== PLAYER INFO =====\n";
  cout << "Name: " << playerName << endl;
  cout << "Bots: 3 (Bot1, Bot2, Bot3)\n";

  if (gameStarted || gameOver) {
    cout << "\n--- Remaining Cards ---\n";
    for (Player* p : currentGame->getPlayers()) {
      cout << p->getName() << ": " << p->getHandSize() << " cards";
      if (gameOver && p->getName() == winnerName) {
        cout << "    WINNER";
      }
      cout << endl;
    }
  }
  cout << endl;
}

int main() {
  GameMode mode;
  cout << mode.getModeName() << endl;

  string playerName;
  cout << "Enter your name: ";
  cin >> playerName;

  int choice;
  while (true) {
    cout << "\n======= UNO GAME MAIN MENU =======\n";
    cout << "1. Start Game\n";
    cout << "2. View Rules\n";
    cout << "3. View Player Info\n";
    cout << "4. Exit\n";
    cout << "==================================\n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
      cout << "\nStarting the UNO game for " << playerName << "...\n\n";
      currentGame = new Game(playerName, &mode);
      gameStarted = true;
      currentGame->start();
      gameOver = true;
      winnerName = currentGame->getWinnerName();
    } else if (choice == 2) {
      showRules();
    } else if (choice == 3) {
      if (playerName.empty()) {
        cout << "You must start a game first to enter your name.\n\n";
      } else {
        showPlayerInfo(playerName);
      }
    } else if (choice == 4) {
      cout << "Exiting UNO Game. Bye!\n";
      break;
    } else {
      cout << "Invalid choice. Please try again.\n";
    }
  }

  delete currentGame; // clean up game pointer
  return 0;
}