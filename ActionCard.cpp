#include "ActionCard.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

ActionCard::ActionCard(Color color, ActionType type) : Card(color, Action)
{
  this->action = type;
}

ActionType ActionCard::get_ActionType() const { return action; }

// Check if card can be played
bool ActionCard::canPlayOn(Card *topCard)
{
  if (topCard == nullptr)
  {
    return true;
  }

  // Wild and Wild Draw Four can be played anytime
  if (action == Wild || action == Wild_Draw_Four || action == topCard->get_ActionType())
  {
    return true;
  }

  // Otherwise, must match color
  return topCard->get_Color() == color;
}

void ActionCard::play(Game *game)
{
  std::cout << "Played Action Card: " << toString() << " | ";

  switch (action)
  {
  case Skip:
    cout << " Skipping " << endl;
    game->skipNextPlayer();
    cout << " Skipped " << endl;
    break;
  case Reverse:
    cout << " Reversing " << endl;
    game->reverseDirection();
    cout << " Reversed " << endl;
    break;
  case Draw_Two:
    game->forceDraw(2);
    game->skipNextPlayer(); // Next player misses turn
    break;
  case Wild:
  case Wild_Draw_Four:
    bool isHuman = game->getCurrentPlayer()->isHuman();
    if (action == Wild_Draw_Four)
    {
      cout << "-----------force draw------------" << endl;
      game->forceDraw(4);
      cout << "-----------skipping------------" << endl;
      game->skipNextPlayer();
    }

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

      break;
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

      break;
    }
  }

  game->updateCurrentCard(this); // Set this card as top card
}

std::string ActionCard::toString()
{
  std::string colorStr;

  switch (color)
  {
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
    colorStr = "";
    break;
  }

  std::string actionStr;

  switch (action)
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
  case Wild:
    actionStr = "Wild";
    break;
  case Wild_Draw_Four:
    actionStr = "Wild Draw Four";
    break;
  default:
    actionStr = "Unknown Action";
    break;
  }

  return colorStr + " " + actionStr;
}

int ActionCard::get_number() { return 99; }

ActionType ActionCard::get_ActionType() { return this->action; }

string ActionCard::get_ActionTypeString()
{
  switch (action)
  {
  case Skip:
    return "Skip";
  case Reverse:
    return "Reverse";
  case Draw_Two:
    return "Draw Two";
  case Wild:
    return "Wild";
  case Wild_Draw_Four:
    return "Wild Draw Four";
  default:
    return "Unknown";
  }
}
