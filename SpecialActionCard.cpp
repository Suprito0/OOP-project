#include "SpecialActionCard.h"
#include "Game.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

SpecialActionCard::SpecialActionCard(Color color)
    : ActionCard(color, Wild) {    // Use Wild as base type for compatibility
  std::srand(std::time(nullptr));  // Seed random generator once
  randAction();                    // Assign a random action
}

// Randomly select a special action
void SpecialActionCard::randAction() {
  // Only choose among these actions for special effect
  int actionIndex = std::rand() % 3;  // 0, 1, or 2

  switch (actionIndex) {
    case 0:
      selectedAction = Skip;
      break;
    case 1:
      selectedAction = Reverse;
      break;
    case 2:
      selectedAction = Draw_Two;
      break;
  }
}

// Return the selected random action
ActionType SpecialActionCard::get_SelectedAction() const {
  return selectedAction;
}

// Play the randomly selected action
void SpecialActionCard::play(Game* game) {
  std::cout << "Played Special Action Card: " << toString() << std::endl;

  bool isHuman = game->getCurrentPlayer()->isHuman();

  switch (selectedAction) {
    case Skip:
      game->skipNextPlayer();
      break;
    case Reverse:
      game->reverseDirection();
      break;
    case Draw_Two:
      game->forceDraw(2);
      game->skipNextPlayer();
      break;
    default:
      std::cout << "Unknown special action.\n";
      break;
  }

  // Ask player to choose a new color
  if (isHuman)
    {
      // Ask player to choose a color
      int choice = -1;

      while (choice < 0 || choice > 3)
      {
        std::cout << "Choose a color:\n";
        std::cout << "0. Red\n1. Green\n2. Blue\n3. Yellow\n> ";
        std::cin >> choice;

        if (choice < 0 || choice > 3)
        {
          std::cout
              << "Invalid choice. Please enter a number between 0 and 3.\n";
        }
      }
      game->changeColor(static_cast<Color>(choice));

      // Show color confirmation
      switch (choice)
      {
      case 0:
        std::cout << "Color changed to Red.\n";
        break;
      case 1:
        std::cout << "Color changed to Green.\n";
        break;
      case 2:
        std::cout << "Color changed to Blue.\n";
        break;
      case 3:
        std::cout << "Color changed to Yellow.\n";
        break;
      default:
        std::cout << "Invalid choice.\n";
        break;
      }
    }
    else
    {
      Color choice = game->getCurrentPlayer()->chooseOptimalColor();
      game->changeColor(choice);
      switch (choice)
      {
      case Red:
        std::cout << "Color changed to Red.\n";
        break;
      case Green:
        std::cout << "Color changed to Green.\n";
        break;
      case Blue:
        std::cout << "Color changed to Blue.\n";
        break;
      case Yellow:
        std::cout << "Color changed to Yellow.\n";
        break;
      default:
        std::cout << "Invalid choice.\n";
        break;
      }
    }

  game->updateCurrentCard(this);
}

// Convert to string
std::string SpecialActionCard::toString() {
  std::string colorStr;
  switch (color) {
    case Red:
      colorStr = "Red";
      break;
    case Green:
      colorStr = "Green";
      break;
    case Blue:
      colorStr = "Blue";
      break;
    case Yellow:
      colorStr = "Yellow";
      break;
    default:
      colorStr = "None";
      break;
  }

  std::string actionStr;
  switch (selectedAction) {
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

  return colorStr + " Special " + actionStr;
}

ActionType SpecialActionCard::get_ActionType(){
  return this->selectedAction;
}