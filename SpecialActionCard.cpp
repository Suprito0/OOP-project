#include "SpecialActionCard.h"
#include "Game.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

SpecialActionCard::SpecialActionCard(Color color, ActionType type)
    : ActionCard(color, type)
{
  this->targetPlayerIndex = -1;
}

// Randomly select a special action
// void SpecialActionCard::randAction()
// {
//   // Only choose among these actions for special effect
//   int actionIndex = std::rand() % 3; // 0, 1, or 2

//   switch (actionIndex)
//   {
//   case 0:
//     selectedAction = Skip;
//     break;
//   case 1:
//     selectedAction = Reverse;
//     break;
//   case 2:
//     selectedAction = Draw_Two;
//     break;
//   }
// }

// Return the selected random action
// ActionType SpecialActionCard::get_SelectedAction() const
// {
//   return selectedAction;
// }

// Select a player
void SpecialActionCard::play(Game *game)
{
  std::cout << "Played Special Action Card: " << toString() << std::endl;

  string targetPlayerIndexString;

  bool isHuman = game->getCurrentPlayer()->isHuman();
  if (isHuman)
  {
    cout << "Choose which Player to Target- |";
    for (int i = 0; i < 4; i++)
    {
      if (i != game->getCurrentPlayerIndex())
      {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName() << " |";
      }
      else
      {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName() << "(You) |";
      }
    }
    cout << endl;

    while (true)
    {
      cin >> targetPlayerIndexString;
      if (targetPlayerIndexString == "0")
      {
        this->targetPlayerIndex = 0;
        break;
      }
      else if (targetPlayerIndexString == "1")
      {
        this->targetPlayerIndex = 1;
        break;
      }
      else if (targetPlayerIndexString == "2")
      {
        this->targetPlayerIndex = 2;
        break;
      }
      else if (targetPlayerIndexString == "3")
      {
        this->targetPlayerIndex = 3;
        break;
      }
      else
      {
        cout << "Invalid Input. Please try again." << endl;
      }
    }
  }
  else
  {
    while (true)
    {
      srand(time(nullptr));
      int randomIndex = rand() % 4;
      if (game->getCurrentPlayerIndex() != randomIndex)
      {
        this->targetPlayerIndex = randomIndex;
        break;
      }
    }
  }

  game->changeColor(this->get_Color());
  cout << game->getCurrentPlayer()->getName() << " has targetted " << game->getPlayer(this->targetPlayerIndex)->getName() << endl;
  game->updateCurrentCard(this);
}
// Convert to string
std::string SpecialActionCard::toString()
{
  std::string colorStr;
  switch (color)
  {
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
  switch (this->action)
  {
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

ActionType SpecialActionCard::get_ActionType()
{
  return this->selectedAction;
}

string SpecialActionCard::get_CardTypeString()
{
  return "Special " + this->get_ActionTypeString();
}

void SpecialActionCard::specialAction(Game *game)
{
  if (this->targetPlayerIndex != -1 && game->getCurrentPlayer()->getIndex() == this->targetPlayerIndex)
  {
    // bool isHuman = game->getCurrentPlayer()->isHuman();

    switch (this->action)
    {
    case Reverse:
      game->reverseDirection();
      break;
    case Draw_Two:
      game->specialDraw(2);
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

int SpecialActionCard::get_TargetPlayerIndex() { return this->targetPlayerIndex; }

// // Ask player to choose a new color
// if (isHuman)
// {
//   // Ask player to choose a color
//   int choice = -1;

//   while (choice < 0 || choice > 3)
//   {
//     std::cout << "Choose a color:\n";
//     std::cout << "0. Red\n1. Green\n2. Blue\n3. Yellow\n> ";
//     std::cin >> choice;

//     if (choice < 0 || choice > 3)
//     {
//       std::cout
//           << "Invalid choice. Please enter a number between 0 and 3.\n";
//     }
//   }
//   game->changeColor(static_cast<Color>(choice));

//   // Show color confirmation
//   switch (choice)
//   {
//   case 0:
//     std::cout << "Color changed to Red.\n";
//     break;
//   case 1:
//     std::cout << "Color changed to Green.\n";
//     break;
//   case 2:
//     std::cout << "Color changed to Blue.\n";
//     break;
//   case 3:
//     std::cout << "Color changed to Yellow.\n";
//     break;
//   default:
//     std::cout << "Invalid choice.\n";
//     break;
//   }
// }
// else
// {
//   Color choice = game->getCurrentPlayer()->chooseOptimalColor();
//   game->changeColor(choice);
//   switch (choice)
//   {
//   case Red:
//     std::cout << "Color changed to Red.\n";
//     break;
//   case Green:
//     std::cout << "Color changed to Green.\n";
//     break;
//   case Blue:
//     std::cout << "Color changed to Blue.\n";
//     break;
//   case Yellow:
//     std::cout << "Color changed to Yellow.\n";
//     break;
//   default:
//     std::cout << "Invalid choice.\n";
//     break;
//   }
// }