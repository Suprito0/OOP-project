#include "NumberCard.h"
#include "Game.h"
#include <iostream>

NumberCard::NumberCard(Color color,int num) :Card(color, Number){
    this->number=num;
}

int NumberCard::get_Number() const{
    return number;
}

// Implement the canPlayOn method (checks if the top card matches the number or color)
bool NumberCard::canPlayOn(Card* topCard) {
    if (topCard == nullptr){
        return true; // If no top card, you can play any card
    }
    // Check if the top card is a NumberCard
    if (topCard->get_CardType() == Number) {
        // Compare number or color directly
        NumberCard* topNumberCard = dynamic_cast<NumberCard*>(topCard);
        return topNumberCard && (topNumberCard->get_Number() == number || topNumberCard->get_Color() == color);
    }

    // If the top card is an action or special card, you can play based on color
    return topCard->get_Color() == color;
}

void NumberCard::play(Game* game) {
    // Implement the logic to handle the effect of the card being played
    std::cout << "Played Number Card: " << toString() << std::endl;
}

// Implement the toString method (return string representation of the card)
std::string NumberCard::toString() {
    std::string colorStr;
    switch (color) {
        case Red: colorStr = "Red"; break;
        case Green: colorStr = "Green"; break;
        case Blue: colorStr = "Blue"; break;
        case Yellow: colorStr = "Yellow"; break;
        default: colorStr = "None"; break;
    }

    return colorStr + " " + std::to_string(number);
}