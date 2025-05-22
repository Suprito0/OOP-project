#include <iostream>

#include "AIPlayer.h"
#include "Deck.h"
#include "Game.h"
#include "GameMode.h"
#include "HumanPlayer.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"
using namespace std;

void showRules() {
  std::cout << "\n===== UNO RULES =====\n";
  std::cout << "1. Each player starts with 7 cards.\n";
  std::cout << "2. The objective is to be the first player to get rid of all "
               "cards.\n";
  std::cout
      << "3. On your turn, match the top card by number, color, or action.\n";
  std::cout << "   Wild and Wild Draw Four cards can be played at any time.\n";
  std::cout << "4. If you can't play, draw a card.\n";
  std::cout << "5. Action cards:\n";
  std::cout << "   - Skip: Next player loses a turn\n";
  std::cout << "   - Reverse: Reverses direction\n";
  std::cout << "   - Draw Two: Next player draws 2 cards and skips turn\n";
  std::cout << "   - Wild: You choose the next color\n";
  std::cout << "   - Wild Draw Four: Choose a color and next player draws 4 + "
               "skips\n";
  std::cout << "6. Special Action card (your custom rule):\n";
  std::cout
      << "   - Choose an action card and target a player of your choice\n";
  std::cout
      << "7. UNO rule: Type 0 BEFORE playing your last card to call UNO.\n\n";
}

void showPlayerInfo(const string& playerName) {
  cout << "===== PLAYER INFO =====\n";
  cout << "Name: " << playerName << endl;
  cout << "Bots: 3 (Bot1, Bot2, Bot3)\n\n";
}

int main() {
  GameMode mode;
  cout << mode.getModeName() << endl;

  string playerName;
  cout << "Enter your name: " << endl;
  cin >> playerName;

  int choice;

  while (true) {
    cout << "======= UNO GAME MAIN MENU =======\n";
    cout << "1. Start Game\n";
    cout << "2. View Rules\n";
    cout << "3. View Player Info\n";
    cout << "4. Exit\n";
    cout << "==================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      cout << "\nStarting the UNO game for " << playerName << "...\n\n";
      Game game(playerName, &mode);
      game.start();
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

  // Game game(playerName, &mode);
  // game.start();
}
