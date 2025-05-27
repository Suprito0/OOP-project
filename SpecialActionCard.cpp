#include "SpecialActionCard.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "Player.h"

// Constructor: Initializes the special action card with a color and action type.
// Sets the card type to Special_Action and initializes the target player index to -1 (no target yet).
SpecialActionCard::SpecialActionCard(Color color, ActionType actionType)
    : ActionCard(color, actionType)
{
  this->type = Special_Action;
  this->targetPlayerIndex = -1;
}

// play(): Called when this card is played by a player.
// Allows the human or AI to choose a target player for the action.
void SpecialActionCard::play(Game *game)
{
  cout << "Played Special Action Card: " << toString() << endl;

  string targetPlayerIndexString;

  // Check if the current player is a human or AI
  bool isHuman = game->getCurrentPlayer()->isHuman();

  if (isHuman)
  {
    // Display all players for the human to choose a target
    cout << "Choose which Player to Target- |";
    for (int i = 0; i < 4; i++)
    {
      if (!game->getPlayer(i))
      {
        cerr << "Error: null player reference in SpecialActionCard::play()\n";
        return;
      }
      // Show each player and mark the current player as "(You)"
      if (i != game->getCurrentPlayerIndex())
      {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << " |";
      }
      else
      {
        cout << " Player " << i << ": " << game->getPlayer(i)->getName()
             << "(You) |";
      }
    }
    cout << endl;

    // Ask the human player to enter a valid player index (0-3)
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
    // For AI player: choose a random player (not itself) as target
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

  // Change the game's current color to the card's color
  game->changeColor(this->get_Color());
  // Show the targeting result
  cout << game->getCurrentPlayer()->getName() << " has targetted "
       << game->getPlayer(this->targetPlayerIndex)->getName() << endl;
  // Set this card as the top card in the game
  game->updateCurrentCard(this);
}

// toString(): Returns a string representation of the special action card.
// Format: "Red Special Skip", "Green Special Reverse", etc.
string SpecialActionCard::toString()
{
  string colorStr;
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

  string actionStr;
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

// specialAction(): Called later to apply the effect of the card to the targeted player.
// If it's that player's turn (or will be skipped), apply the corresponding action.
void SpecialActionCard::specialAction(Game *game, bool willSkip)
{
  if (this->targetPlayerIndex != -1 &&
      (game->getCurrentPlayer()->getIndex() == this->targetPlayerIndex ||
       (game->getPreviousPlayer()->getIndex() == this->targetPlayerIndex && willSkip)))
  {
    switch (this->action)
    {
    case Reverse:
      game->reverseDirection();
      break;
    case Draw_Two:
      game->specialDraw(2, this->targetPlayerIndex);
      break;
    case Skip:
      cout << "Special Skip" << endl;
      break;
    default:
      cout << "Unknown special action.\n";
      break;
    }
    // Reset target after action is applied
    this->targetPlayerIndex = -1;
  }
}

// get_TargetPlayerIndex(): Returns the index of the currently targeted player
int SpecialActionCard::get_TargetPlayerIndex()
{
  return this->targetPlayerIndex;
}