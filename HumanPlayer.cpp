#include "HumanPlayer.h"

#include <iostream>

#include "ActionCard.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"

HumanPlayer::HumanPlayer() : Player() { this->isItHuman = true; }

HumanPlayer::HumanPlayer(string name) : Player(name) { this->isItHuman = true; }

Card *HumanPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks) {
  while (true) {
    displayHand();

    std::cout << "\n=== YOUR TURN MENU ===\n";
    std::cout << "1. Play a card\n";
    std::cout << "2. Draw a card\n";
    std::cout << "3. View Rules\n";
    std::cout << "4. View Player Info\n";
    std::cout << "5. View scoreboard\n";
    std::cout << "6. Exit Game\n";
    std::cout << "======================\n";
    std::cout << "\nEnter your choice: ";

    int choice = -1;
    string choiceString;
    std::cin >> choiceString;
    try {
      choice = stoi(choiceString);
    } catch (const std::exception &e) {
      std::cout << "Invalid input. Please enter a number." << std::endl;
      continue;
    }

    switch (choice) {
      case 1: {  // Play a card

        int input = -100;
        std::string inputString;
        while (true) {
          cout << "Type 'back' to go to the Turn Menu." << endl;
          std::cout << "Select a card to play (1-" << hand.size() << "): ";
          std::cin >> inputString;

          if (this->toLower(inputString) == "back" ||
              this->toLower(inputString) == "bac" ||
              this->toLower(inputString) == "ba" ||
              this->toLower(inputString) == "b") {
            break;
          }

          try {
            input = std::stoi(inputString);

            if (input == 0) {
              this->callUno(true);
              std::cout << "You have called UNO!" << std::endl;
              continue;  // Ask again for card
            }

            if (input >= 1 && input <= static_cast<int>(hand.size())) {
              Card *selectedCard = hand[input - 1];
              if (selectedCard->canPlayOn(topCard) ||
                  selectedCard->get_Color() == currentColor ||
                  selectedCard->get_Color() == None) {
                removeCardFromHand(selectedCard);
                decks->addToDiscardPile(selectedCard);

                return selectedCard;
              } else {
                std::cout
                    << "\nWarning: That card can't be played. Try again.\n";
                if (!hasValidMove(gameRef)) {
                  std::cout << "You have no valid moves. Please draw a card.\n";
                  std::cout << std::endl;
                }
              }
            } else {
              std::cout << "Invalid input. Try again.\n";
            }
          } catch (const std::exception &e) {
            std::cout << "Invalid input. Please enter a number or type 'back' "
                         "to go to the Turn Menu."
                      << std::endl;
            continue;
          }
        }
        break;
      }

      case 2: {  // Draw a card
        std::cout << " Drawing a card...\n";
        Card *newCard = decks->drawCard();

        if (!newCard) {
          return new ActionCard(None, Skip);
        }

        std::cout << "You drew: " << newCard->toString() << std::endl;
        addCardToHand(newCard);
        std::cout << "Turn ended. Next player's turn.\n";
        return nullptr;
      }

      case 3: {  // View rules
        std::cout << "\n===== UNO RULES =====\n";
        std::cout << "1. Match top card by number, color, or action.\n";
        std::cout << "2. Wild and Wild Draw Four can be played anytime.\n";
        std::cout << "3. Action Cards:\n";
        std::cout << "   - Skip: skip next player\n";
        std::cout << "   - Reverse: change direction\n";
        std::cout << "   - Draw Two: next draws 2 cards\n";
        std::cout << "   - Wild: choose the next color\n";
        std::cout << "   - Wild Draw Four: choose color + next draws 4\n";
        std::cout << "4. If you can't play, you must draw.\n";
        std::cout
            << "5. Type 0 before playing your second-last card to call UNO.\n";
        std::cout << std::endl;
        break;
      }

      case 4: {  // View player info
        std::cout << "\n===== PLAYER INFO =====\n";
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Cards in hand: " << hand.size() << std::endl;

        std::cout << "\n--- Other Players ---\n";
        for (int i = 0; i < 4; ++i) {
          if (gameRef->getPlayer(i) != this) {
            std::cout << gameRef->getPlayer(i)->getName() << ": "
                      << gameRef->getPlayer(i)->getHandSize() << " cards\n";
          }
        }
        std::cout << std::endl;
        break;
      }

      case 5:
        gameRef->printScores();
        break;

      case 6:  // Exit
      {
        string willExit;
        while (true) {
          cout << "You are trying to exit the game. Continue? (y/n)\n";
          cin >> willExit;
          willExit = this->toLower(willExit);

          if (willExit == "y" || willExit == "n") {
            break;
          } else {
            cout << "Invalid Input\n";
          }
        }
        if (willExit == "n") {
          continue;
        }
        std::cout << "\nExiting the game. Goodbye!\n";
        exit(0);
        break;
      }

      default:
        std::cout << "Invalid choice. Try again.\n";
    }
  }
}

void HumanPlayer::setGame(Game *g) { gameRef = g; }

bool HumanPlayer::hasValidMove(Game *game) const {
  for (Card *card : hand) {
    if (game->isValidMove(card)) {
      return true;  // found a playable card
    }
  }
  return false;  // no playable cards
}