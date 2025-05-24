#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "Deck.h"

Player::Player()
{
    this->name = "Player";
    this->hasCalledUno = false;
}

Player::Player(string name)
{
    this->name = name;
    this->hasCalledUno = false;
}

// Card* Player::playTurn(Card* topCard, Color currentColor, Deck* draw, Deck* discard){}

void Player::addCardToHand(Card *card)
{
    hand.push_back(card);
}

void Player::removeCardFromHand(Card *card)
{
    for (size_t i = 0; i < hand.size(); i++)
    {
        if (hand[i] == card)
        {
            hand.erase(hand.begin() + i);
        }
    }
}

bool Player::hasValidMove(Card *topCard, Color currentColor)
{
    for (Card *card : hand)
    {
        if (card->canPlayOn(topCard) || card->get_Color() == currentColor)
        {
            return true;
        }
    }
    return false;
}

void Player::callUno(bool uno)
{
    hasCalledUno = uno;
}

size_t Player::getHandSize()
{
    return hand.size();
}

string Player::getName()
{
    return this->name;
}

void Player::displayHand()
{
    // int numCards = hand.size();
    // cout << this->getName() << " : ";
    // for (size_t i = 0; i < numCards; i++)
    // {
    //     std::cout << "Card " << i + 1 << " :" << hand[i]->get_ColorString() <<
    //     " " << hand[i]->get_CardTypeString() << " | ";
    // }
    // std::cout << std::endl;

    std::cout << "\n"
              << this->getName() << "'s Hand:\n";
    std::cout << "--------------------------------------------\n";
    for (size_t i = 0; i < hand.size(); ++i)
    {
        std::cout << "Card " << (i + 1) << ": " << hand[i]->get_ColorString() << hand[i]->get_CardTypeString() << "\n";
    }
    std::cout << "--------------------------------------------\n";
}

bool Player::isHuman()
{
    return this->isItHuman;
}

Color Player::chooseOptimalColor()
{
    int countRed, countGreen, countBlue, countYellow = 0;
    Color currentColour;

    for (Card *card : hand)
    {
        currentColour = card->get_Color();
        switch (currentColour)
        {
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

    if (countGreen > maxCount)
    {
        maxCount = countGreen;
        optimalColour = Green;
    }

    if (countBlue > maxCount)
    {
        maxCount = countBlue;
        optimalColour = Blue;
    }

    if (countYellow > maxCount)
    {
        maxCount = countYellow;
        optimalColour = Yellow;
    }

    return optimalColour;
}

bool Player::getUno()
{
    return this->hasCalledUno;
}

void Player::setIndex(int index)
{
    this->playerIndex = index;
}

int Player::getIndex()
{
    return this->playerIndex;
}

string Player::toLower(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
              [](unsigned char c)
              { return tolower(c); });
    return lowerStr;
}

Player::~Player() {}