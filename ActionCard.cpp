#include "ActionCard.h"

#include <iostream>

#include "Game.h"
#include "Player.h"

ActionCard::ActionCard(Color color, ActionType ActionType)
    : Card(color, Action)
{
  this->action = ActionType;
}

// Check if card can be played
bool ActionCard::canPlayOn(Card *topCard)
{
  if (topCard == nullptr)
  {
    return true;
  }

  // Wild and Wild Draw Four can be played anytime
  if (action == Wild || action == Wild_Draw_Four ||
      this->action == topCard->get_ActionType())
  {
    return true;
  }

  // Otherwise, must match color
  return topCard->get_Color() == color;
}

void ActionCard::play(Game *game)
{
  string targetPlayerName = game->isFirstTurn() ? game->getCurrentPlayer()->getName() : game->getNextPlayer()->getName();
  cout << "Played Action Card: " << toString() << " | " << endl;

  switch (action)
  {
  case Skip:
    cout << "Skipping\n";
    game->skipPlayer();
    game->setWillSkip(true);
    cout << "Skipped\n";
    break;

  case Reverse:
    cout << "Reversing\n";
    game->reverseDirection();
    cout << "Direction is now ";
    cout << (game->isClockwise() ? "Clockwise" : "Anti-Clockwise") << endl;
    break;

  case Draw_Two:
    game->isFirstTurn() ? game->specialDraw(2,game->getCurrentPlayerIndex()) : game->forceDraw(2);
      cout << "Skipping " << targetPlayerName << "'s turn\n";
    game->skipPlayer();
    game->setWillSkip(true);
    break;

  case Wild:
  case Wild_Draw_Four:
  {
    bool isHuman = game->getCurrentPlayer()->isHuman();

    if (action == Wild_Draw_Four)
    {
      cout << targetPlayerName;
      cout << " is drawing 4 cards.\n";
      game->isFirstTurn() ? game->specialDraw(4, game->getCurrentPlayerIndex()) : game->forceDraw(4);

      cout << "Skipping " << targetPlayerName << "'s turn\n";
      game->skipPlayer();
    game->setWillSkip(true);
    }
    if (game->isGameError())
    {
      return;
    }

    Color chosenColor;

    if (isHuman)
    {
      string input;
      int choice = -1;

      cout << "Choose a color:\n";
      while (true)
      {
        cout << "1. Red\n2. Green\n3. Blue\n4. Yellow\n> ";
        cin >> input;

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

        cout
            << "Invalid choice. Please enter a number between 1 and 4.\n";
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
      cout << "Color changed to Red.\n";
      break;
    case Green:
      cout << "Color changed to Green.\n";
      break;
    case Blue:
      cout << "Color changed to Blue.\n";
      break;
    case Yellow:
      cout << "Color changed to Yellow.\n";
      break;
    default:
      cout << "Invalid color.\n";
      break;
    }

    break;
  }
  }

  game->updateCurrentCard(this); // Set this card as top card
  if (game->checkForWinner() && (this->get_ActionType() == Skip ||
                                 this->get_ActionType() == Wild_Draw_Four ||
                                 this->get_ActionType() == Draw_Two))
  {
    game->setCurrentPlayerIndex(game->getPreviousPlayer()->getIndex());
  }
}

string ActionCard::toString()
{
  string colorStr;

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

  string actionStr;

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
