#include "HumanPlayer.h"

#include <iostream>

#include "ActionCard.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

HumanPlayer::HumanPlayer() : Player() { this->isItHuman = true; }

HumanPlayer::HumanPlayer(string name) : Player(name) { this->isItHuman = true; }

Card *HumanPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks)
{
  while (true)
  {
    displayHand();

    cout << "\n=== YOUR TURN MENU ===\n";
    cout << "1. Play a card\n";
    cout << "2. Draw a card\n";
    cout << "3. View Rules\n";
    cout << "4. View Player Info\n";
    cout << "5. View scoreboard\n";
    cout << "6. Exit Game\n";
    cout << "======================\n";
    cout << "\nEnter your choice: ";

    int choice = -1;
    string choiceString;
    cin >> choiceString;
    try
    {
      choice = stoi(choiceString);
    }
    catch (const exception &e)
    {
      cout << "Invalid input. Please enter a number." << endl;
      continue;
    }

    switch (choice)
    {
    case 1:
    { // Play a card

      int input = -100;
      string inputString;
      while (true)
      {
        cout << "Type 'back' to go to the Turn Menu." << endl;
        cout << "Select a card to play (1-" << hand.size() << "): ";
        cin >> inputString;

        if (this->toLower(inputString) == "back" ||
            this->toLower(inputString) == "bac" ||
            this->toLower(inputString) == "ba" ||
            this->toLower(inputString) == "b")
        {
          break;
        }

        try
        {
          input = stoi(inputString);

          if (input == 0)
          {
            this->callUno(true);
            cout << "You have called UNO!" << endl;
            continue; // Ask again for card
          }

          if (input >= 1 && input <= static_cast<int>(hand.size()))
          {
            Card *selectedCard = hand[input - 1];
            if (selectedCard->canPlayOn(topCard) ||
                selectedCard->get_Color() == currentColor ||
                selectedCard->get_Color() == None)
            {
              removeCardFromHand(selectedCard);
              decks->addToDiscardPile(selectedCard);

              return selectedCard;
            }
            else
            {
              cout
                  << "\nWarning: That card can't be played. Try again.\n";
              if (!hasValidMove(gameRef))
              {
                cout << "You have no valid moves. Please draw a card.\n";
                cout << endl;
              }
            }
          }
          else
          {
            cout << "Invalid input. Try again.\n";
          }
        }
        catch (const exception &e)
        {
          cout << "Invalid input. Please enter a number or type 'back' "
                  "to go to the Turn Menu."
               << endl;
          continue;
        }
      }
      break;
    }

    case 2:
    { // Draw a card
      cout << " Drawing a card...\n";
      Card *newCard = decks->drawCard();

      if (!newCard)
      {
        return new ActionCard(None, Skip);
      }

      cout << "You drew: " << newCard->toString() << endl;
      addCardToHand(newCard);
      cout << "Turn ended. Next player's turn.\n";
      return nullptr;
    }

    case 3:
    { // View rules
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
      cout << "   - The action will take effect when it is that player's turn\n";
      cout << "7. UNO rule: Type 0 BEFORE playing your last card to call UNO.\n\n";
      break;
    }

    case 4:
    { // View player info
      cout << "\n===== PLAYER INFO =====\n";
      cout << "Name: " << getName() << endl;
      cout << "Cards in hand: " << hand.size() << endl;

      cout << "\n--- Other Players ---\n";
      for (int i = 0; i < 4; ++i)
      {
        if (gameRef->getPlayer(i) != this)
        {
          cout << gameRef->getPlayer(i)->getName() << ": "
               << gameRef->getPlayer(i)->getHandSize() << " cards\n";
        }
      }
      cout << endl;
      break;
    }

    case 5:
      gameRef->printScores();
      break;

    case 6: // Exit
    {
      string willExit;
      while (true)
      {
        cout << "You are trying to exit the game. Continue? (y/n)\n";
        cin >> willExit;
        willExit = this->toLower(willExit);

        if (willExit == "y" || willExit == "n")
        {
          break;
        }
        else
        {
          cout << "Invalid Input\n";
        }
      }
      if (willExit == "n")
      {
        continue;
      }
      cout << "\nExiting the game. Goodbye!\n";
      exit(0);
      break;
    }

    default:
      cout << "Invalid choice. Try again.\n";
    }
  }
}

void HumanPlayer::setGame(Game *game) { gameRef = game; }

bool HumanPlayer::hasValidMove(Game *game) const
{
  for (Card *card : hand)
  {
    if (game->isValidMove(card))
    {
      return true; // found a playable card
    }
  }
  return false; // no playable cards
}