#include "ActionCard.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

ActionCard::ActionCard(Color color, ActionType ActionType) : Card(color, Action)
{
  this->action = ActionType;
}

// ActionType ActionCard::get_ActionType() const { return this->action; }

// Check if card can be played
bool ActionCard::canPlayOn(Card *topCard)
{
  if (topCard == nullptr)
  {
    return true;
  }

  // Wild and Wild Draw Four can be played anytime
  if (action == Wild || action == Wild_Draw_Four || this->action == topCard->get_ActionType())
  {
    return true;
  }

  // Otherwise, must match color
  return topCard->get_Color() == color;
}

// void ActionCard::play(Game *game)
// {
//   std::cout << "Played Action Card: " << toString() << " | " << endl;

//   switch (action)
//   {
//   case Skip:
//     cout << " Skipping " << endl;
//     if (game->checkForWinner()){ break; }
//     game->skipPlayer();
//     cout << " Skipped " << endl;
//     break;
//   case Reverse:
//     cout << " Reversing " << endl;
//     game->reverseDirection();
//     cout << " Reversed " << endl;
//     break;
//   case Draw_Two:
//     game->isFirstTurn() ? game->specialDraw(2) : game->forceDraw(2);
//     // game->forceDraw(2);
//     if (game->checkForWinner()){ break; }
//     game->skipPlayer(); // Next player misses turn
//     break;
//   case Wild:
//   case Wild_Draw_Four:
//     bool isHuman = game->getCurrentPlayer()->isHuman();
//     if (action == Wild_Draw_Four)
//     {
//       cout << "-----------force draw------------" << endl;
//       game->isFirstTurn() ? game->specialDraw(4) : game->forceDraw(4);
//       cout << "-----------skipping------------" << endl;
//       if (game->checkForWinner()){ break; }
//       game->skipPlayer();
//     }

//     if (isHuman)
//     {
//       // Ask player to choose a color
//       int choice = -1;
//       string choiceString;

//       std::cout << "Choose a color:\n";

//       while (true)
//       {
//         std::cout << "1. Red\n2. Green\n3. Blue\n4. Yellow\n> ";
//         std::cin >> choiceString;

//         if (choiceString == "1")
//         {
//           choice = 0;
//           break;
//         }
//         else if (choiceString == "2")
//         {
//           choice = 1;
//           break;
//         }
//         else if (choiceString == "3")
//         {
//           choice = 2;
//           break;
//         }
//         else if (choiceString == "4")
//         {
//           choice = 3;
//           break;
//         }
//         else
//         {
//           std::cout
//               << "Invalid choice. Please enter a number between 1 and 4.\n";
//         }
//       }
//       game->changeColor(static_cast<Color>(choice));

//       // Show color confirmation
//       switch (choice)
//       {
//       case 0:
//         std::cout << "Color changed to Red.\n";
//         break;
//       case 1:
//         std::cout << "Color changed to Green.\n";
//         break;
//       case 2:
//         std::cout << "Color changed to Blue.\n";
//         break;
//       case 3:
//         std::cout << "Color changed to Yellow.\n";
//         break;
//       default:
//         std::cout << "Invalid choice.\n";
//         break;
//       }

//       break;
//     }
//     else
//     {
//       Color choice = game->getCurrentPlayer()->chooseOptimalColor();
//       game->changeColor(choice);
//       switch (choice)
//       {
//       case Red:
//         std::cout << "Color changed to Red.\n";
//         break;
//       case Green:
//         std::cout << "Color changed to Green.\n";
//         break;
//       case Blue:
//         std::cout << "Color changed to Blue.\n";
//         break;
//       case Yellow:
//         std::cout << "Color changed to Yellow.\n";
//         break;
//       default:
//         std::cout << "Invalid choice.\n";
//         break;
//       }

//       break;
//     }
//   }

//   game->updateCurrentCard(this); // Set this card as top card
// }

void ActionCard::play(Game *game)
{
  std::cout << "Played Action Card: " << toString() << " | " << std::endl;

  switch (action)
  {
  case Skip:
    std::cout << "Skipping\n";
    game->skipPlayer();
    std::cout << "Skipped\n";
    break;

  case Reverse:
    std::cout << "Reversing\n";
    game->reverseDirection();
    std::cout << "Reversed\n";
    break;

  case Draw_Two:
    game->isFirstTurn() ? game->specialDraw(2) : game->forceDraw(2);
    game->skipPlayer();
    break;

  case Wild:
  case Wild_Draw_Four:
  {
    bool isHuman = game->getCurrentPlayer()->isHuman();

    if (action == Wild_Draw_Four)
    {
      std::cout << "-----------Force Draw------------\n";
      game->isFirstTurn() ? game->specialDraw(4) : game->forceDraw(4);

      std::cout << "-----------Skipping------------\n";
      game->skipPlayer();
    }
    if (game->isGameError())
    {
      return;
    }

    Color chosenColor;

    if (isHuman)
    {
      std::string input;
      int choice = -1;

      std::cout << "Choose a color:\n";
      while (true)
      {
        std::cout << "1. Red\n2. Green\n3. Blue\n4. Yellow\n> ";
        std::cin >> input;

        if (input == "1")
        {
          choice = 0;
          break;
        }
        else if (input == "2")
        {
          choice = 1;
          break;
        }
        else if (input == "3")
        {
          choice = 2;
          break;
        }
        else if (input == "4")
        {
          choice = 3;
          break;
        }

        std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
      }

      chosenColor = static_cast<Color>(choice);
    }
    else
    {
      chosenColor = game->getCurrentPlayer()->chooseOptimalColor();
    }

    game->changeColor(chosenColor);

    // Confirmation message
    switch (chosenColor)
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
      std::cout << "Invalid color.\n";
      break;
    }

    break;
  }
  }

  game->updateCurrentCard(this); // Set this card as top card
  if (game->checkForWinner() && (this->get_ActionType() == Skip || this->get_ActionType() == Wild_Draw_Four || this->get_ActionType() == Draw_Two))
  {
    game->setCurrentPlayerIndex(game->getPreviousPlayer()->getIndex());
  }
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

string ActionCard::get_CardTypeString()
{
  switch (this->type)
  {
  case Action:
    return "Action";
  case Special_Action:
    return "Special_Action";
  default:
    return "Unknown";
  }
}