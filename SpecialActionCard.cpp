#include "SpecialActionCard.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "Player.h"

SpecialActionCard::SpecialActionCard(Color color, ActionType actionType)
    : ActionCard(color, actionType) {
  this->type = Special_Action;
  this->targetPlayerIndex = -1;
}

void SpecialActionCard::play(Game *game) {
  std::cout << "Played Special Action Card: " << toString() << std::endl;

  string targetPlayerIndexString;

  bool isHuman = game->getCurrentPlayer()->isHuman();

  if (isHuman) {
    cout << "Choose which Player to Target- |";
    for (int i = 0; i < 4; i++) {
      if (!game->getPlayer(i)) {
        cerr << "Error: null player reference in SpecialActionCard::play()\n";
        return;
      }
      if (i != game->getCurrentPlayerIndex()) {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << " |";
      } else {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << "(You) |";
      }
    }
    cout << endl;

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
    while (true) {
      srand(time(nullptr));
      int randomIndex = rand() % 4;
      if (game->getCurrentPlayerIndex() != randomIndex) {
        this->targetPlayerIndex = randomIndex;
        break;
      }
    }
  }

  game->changeColor(this->get_Color());
  cout << game->getCurrentPlayer()->getName() << " has targetted "
       << game->getPlayer(this->targetPlayerIndex)->getName() << endl;
  game->updateCurrentCard(this);
}
// Convert to string
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

void SpecialActionCard::specialAction(Game *game) {
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
    this->targetPlayerIndex = -1;
  }
}

int SpecialActionCard::get_TargetPlayerIndex() {
  return this->targetPlayerIndex;
}