#include "SpecialActionCard.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "Player.h"

// Constructor: initializes a special action card with color and action type
SpecialActionCard::SpecialActionCard(Color color, ActionType actionType)
    : ActionCard(color, actionType) {
  this->type = Special_Action;
  this->targetPlayerIndex = -1;
}

// This function is called when the card is played
void SpecialActionCard::play(Game *game) {
  std::cout << "Played Special Action Card: " << toString() << std::endl;

  string targetPlayerIndexString;

  bool isHuman = game->getCurrentPlayer()->isHuman();

  if (isHuman) {
    // Show all players for target selection
    cout << "Choose which Player to Target- |";
    for (int i = 0; i < 4; i++) {
      if (!game->getPlayer(i)) {
        cerr << "Error: null player reference in SpecialActionCard::play()\n";
        return;
      }
      // Mark the current player as "(You)"
      if (i != game->getCurrentPlayerIndex()) {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << " |";
      } else {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << "(You) |";
      }
    }
    cout << endl;

    // Let human player input a valid target
    while (true) {
      cin >> targetPlayerIndexString;
      if (targetPlayerIndexString == "0") {
        this->targetPlayerIndex = 0;
        break;
      } else if (targetPlayerIndexString == "1") {
        this->targetPlayerIndex = 1;
        break;
      } else if (targetPlayerIndexString == "2") {
        this->targetPlayerIndex = 2;
        break;
      } else if (targetPlayerIndexString == "3") {
        this->targetPlayerIndex = 3;
        break;
      } else {
        cout << "Invalid Input. Please try again." << endl;
      }
    }
  } else {
    // Randomly choose a valid target for bot player
    while (true) {
      srand(time(nullptr));
      int randomIndex = rand() % 4;
      // Ensure bot doesn't target itself
      if (game->getCurrentPlayerIndex() != randomIndex) {
        this->targetPlayerIndex = randomIndex;
        break;
      }
    }
  }
  // Change current color to the card's color
  game->changeColor(this->get_Color());
  // Show who is targeted
  cout << game->getCurrentPlayer()->getName() << " has targetted "
       << game->getPlayer(this->targetPlayerIndex)->getName() << endl;
  // Update the top card in the game
  game->updateCurrentCard(this);
}

// Convert card information into a string like "Red Special Draw Two"
std::string SpecialActionCard::toString() {
  std::string colorStr;
  switch (color) {
    case Red:
      colorStr = "Red ";
      break;
    case Green:
      colorStr = "Green ";
      break;
    case Blue:
      colorStr = "Blue ";
      break;
    case Yellow:
      colorStr = "Yellow ";
      break;
    default:
      colorStr = "None";
      break;
  }

  std::string actionStr;
  switch (this->action) {
    case Skip:
      actionStr = "Skip";
      break;
    case Reverse:
      actionStr = "Reverse";
      break;
    case Draw_Two:
      actionStr = "Draw Two";
      break;
    default:
      actionStr = "Unknown";
      break;
  }

  return colorStr + "Special " + actionStr;
}

string SpecialActionCard::get_CardTypeString() {
  return "Special " + this->get_ActionTypeString();
}

// This function is called by Game class to apply the effect of this special card
void SpecialActionCard::specialAction(Game *game) {
  // Only apply effect if current or skipped player is the target
  if (this->targetPlayerIndex != -1 &&
      game->getCurrentPlayer()->getIndex() == this->targetPlayerIndex) {
    switch (this->action) {
      case Reverse:
        game->reverseDirection();
        break;
      case Draw_Two:
        game->specialDraw(2);
        break;
      case Skip:
        cout << "Special Skip" << endl;
        break;
      default:
        std::cout << "Unknown special action.\n";
        break;
    }
    // Reset target after action is done
    this->targetPlayerIndex = -1;
  }
}

// Getter for target player index
int SpecialActionCard::get_TargetPlayerIndex() {
  return this->targetPlayerIndex;
}