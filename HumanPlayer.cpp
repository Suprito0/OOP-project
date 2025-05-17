#include "HumanPlayer.h"
#include "Deck.h"
#include <iostream>

HumanPlayer::HumanPlayer(): Player() {}

HumanPlayer::HumanPlayer(string name): Player(name){}

Card* HumanPlayer::playTurn(Card* topCard, Color currentColor, Deck* decks){
    displayHand();   // Show hand

    if (hasValidMove(topCard, currentColor) == true) {   // Check if there is a valid move
        Card* playCard = nullptr;

        while (true) {
            playCard = selectCard();

            if (playCard->canPlayOn(topCard)) {
                decks->addToDiscardPile(playCard);
                removeCardFromHand(playCard);
                return playCard;
            } else {
                std::cout << "That can't be played! Try again." << std::endl;   // Loops while card selected cannot be played
            }
        }
    } else {
        std::cout << "You have no playable cards! Drawing card." << std::endl;
        Card* newCard = decks->drawCard();
        addCardToHand(newCard);
        return nullptr;
    }
}

void HumanPlayer::displayHand(){
    int numCards = hand.size();

    for (size_t i = 0; i < numCards; i++) {
        std::cout << "Card " << i+1 << " :" << hand[i]->get_Color() << " " << hand[i]->get_CardType() << " | ";
    }
    std::cout << std::endl;
}

Card* HumanPlayer::selectCard(){
    int selectedCard = -1;
    Card* p_selectedCard = nullptr;

    while (selectedCard < 0 || selectedCard > hand.size()) {   // Loops if selected card is not within boundary
        std::cout << "What card would you like to play? Choose from Card 1-" << hand.size() << std::endl;
        std::cin >> selectedCard;
        if (std::cin.fail() || selectedCard < 0 || selectedCard > hand.size()) {
            std::cout << "Invalid input. Try again." << std::endl;
        }
    }
    
    p_selectedCard = hand[selectedCard-1];
    return p_selectedCard;
}

Color HumanPlayer::selectColor(){
    std::string newColour;

    while (true) {
        std::cout << "What colour would you like it to be?" << std::endl;
        std::cout << "Choose Red, Green, Blue or Yellow." << std::endl;
        std::cin >> newColour;

    if (newColour == "Red") {
        return Red;
    } else if (newColour == "Green") {
        return Green;
    } else if (newColour == "Blue") {
        return Blue;
    } else if (newColour == "Yellow") {
        return Yellow;
    } else {
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}
}
