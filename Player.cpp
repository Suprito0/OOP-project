#include "Player.h"

#include <algorithm>

#include "Card.h"
#include "Deck.h"

Player::Player() {
  this->name = "Player";
  this->hasCalledUno = false;
}

Player::Player(string name) {
  this->name = name;
  this->hasCalledUno = false;
}

void Player::addCardToHand(Card *card) { hand.push_back(card); }

void Player::removeCardFromHand(Card *card) {
  for (size_t i = 0; i < hand.size(); i++) {
    if (hand[i] == card) {
      hand.erase(hand.begin() + i);
    }
  }
}

void Player::callUno(bool uno) { hasCalledUno = uno; }

size_t Player::getHandSize() { return hand.size(); }

string Player::getName() { return this->name; }

void Player::displayHand() {
  std::cout << "\n" << this->getName() << "'s Hand:\n";
  std::cout << "--------------------------------------------\n";
  for (size_t i = 0; i < hand.size(); ++i) {
    if (hand[i]->get_CardType() == Special_Action) {
      std::cout << "Card " << (i + 1) << ": " << hand[i]->get_ColorString()
                << "Special " << hand[i]->get_ActionTypeString() << "\n";
      continue;
    }
    std::cout << "Card " << (i + 1) << ": " << hand[i]->get_ColorString()
              << hand[i]->get_ActionTypeString() << "\n";
  }
  std::cout << "--------------------------------------------\n";
}

bool Player::isHuman() { return this->isItHuman; }

Color Player::chooseOptimalColor() {
  int countRed = 0, countGreen = 0, countBlue = 0, countYellow = 0;
  Color currentColour;

  for (Card *card : hand) {
    currentColour = card->get_Color();
    switch (currentColour) {
      case Red:
        countRed++;
        break;
      case Green:
        countGreen++;
        break;
      case Blue:
        countBlue++;
        break;
      case Yellow:
        countYellow++;
        break;
      default:
        break;
    }
  }

  Color optimalColour = Red;
  int maxCount = countRed;

  if (countGreen > maxCount) {
    maxCount = countGreen;
    optimalColour = Green;
  }

  if (countBlue > maxCount) {
    maxCount = countBlue;
    optimalColour = Blue;
  }

  if (countYellow > maxCount) {
    maxCount = countYellow;
    optimalColour = Yellow;
  }

  return optimalColour;
}

bool Player::getUno() { return this->hasCalledUno; }

void Player::setIndex(int index) { this->playerIndex = index; }

int Player::getIndex() { return this->playerIndex; }

string Player::toLower(const string &str) {
  string lowerStr = str;
  transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
            [](unsigned char c) { return tolower(c); });
  return lowerStr;
}

int Player::calculateScore() {  // Calculates score earned by each of the losing
                                // players hands'
  int score = 0;
  int add = 0;
  CardType type;

  for (Card *card : hand) {  // Scores vary by type of card remaining
    type = card->get_CardType();

    switch (type) {
      case Number:
        add = card->get_number();
        score += add;
        break;

      case Action:
        if (card->get_ActionType() == Wild) {
          add = 40;
          score += add;
          break;
        } else if (card->get_ActionType() == Wild_Draw_Four) {
          add = 50;
          score += add;
          break;
        } else {
          add = 20;
          score += add;
          break;
        }

      case Special_Action:
        add = 30;
        score += add;
        break;

      default:
        break;
    }
  }

  return score;
}

Player::~Player() {}