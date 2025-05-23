#include "HumanPlayer.h"
#include "Card.h"
#include "Deck.h"
#include <iostream>

HumanPlayer::HumanPlayer() : Player() { this->isItHuman = true; }

HumanPlayer::HumanPlayer(string name) : Player(name) { this->isItHuman = true; }

Card *HumanPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks)
{
    displayHand(); // Show hand

    if (hasValidMove(topCard, currentColor) == true)
    { // Check if there is a valid move
        Card *playCard = nullptr;

        while (true)
        {
            playCard = selectCard();

            if (playCard->canPlayOn(topCard) || playCard->get_Color() == currentColor)
            {
                decks->addToDiscardPile(playCard);
                removeCardFromHand(playCard);
                return playCard;
            }
            else
            {
                std::cout << "That can't be played! Try again." << std::endl; // Loops while card selected cannot be played
            }
        }
    }
    else
    {
        std::cout << "You have no playable cards! Drawing card." << std::endl;
        Card *newCard = decks->drawCard();
        addCardToHand(newCard);
        return nullptr;
    }
}

// void HumanPlayer::displayHand(){
//     int numCards = hand.size();
//         cout << this->getName() << " : " ;
//     for (size_t i = 0; i < numCards; i++) {
//         std::cout << "Card " << i+1 << " :" << hand[i]->get_ColorString() << " " << hand[i]->get_CardTypeString() << " | ";
//     }
//     std::cout << std::endl;
// }

Card *HumanPlayer::selectCard()
{
    int selectedCard = -1;
    std::string selectedCardString;
    Card *p_selectedCard = nullptr;

    while (true)
    {
        std::cout << "What card would you like to play? Choose from Card 1-" << hand.size() << " (Enter 0 to call UNO)" << std::endl;
        std::cin >> selectedCardString;

        try
        {
            selectedCard = std::stoi(selectedCardString);

            if (selectedCard == 0)
            {
                this->callUno(true);
                std::cout << "You have called UNO!" << std::endl;
                continue; // Ask again for card
            }

            if (selectedCard < 1 || selectedCard > hand.size())
            {
                std::cout << "Invalid input. Please choose a card number from 1 to " << hand.size() << "." << std::endl;
            }
            else
            {
                p_selectedCard = hand[selectedCard - 1];
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid input. Please enter a number." << std::endl;
        }
    }

    return p_selectedCard;
}

// Color HumanPlayer::selectColor()
// {
//     std::string newColour;

//     while (true)
//     {
//         std::cout << "What colour would you like it to be?" << std::endl;
//         std::cout << "Choose Red, Green, Blue or Yellow." << std::endl;
//         std::cin >> newColour;

//         if (newColour == "Red")
//         {
//             return Red;
//         }
//         else if (newColour == "Green")
//         {
//             return Green;
//         }
//         else if (newColour == "Blue")
//         {
//             return Blue;
//         }
//         else if (newColour == "Yellow")
//         {
//             return Yellow;
//         }
//         else
//         {
//             std::cout << "Invalid input. Please try again." << std::endl;
//         }
//     }
// }
