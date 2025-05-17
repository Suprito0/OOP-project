#include "Player.h"

Card* Player::playTurn(Card* topCard, Color currentColor){}

void Player::addCardToHand(Card* card) {
    hand.push_back(card);
}

void Player::removeCardFromHand(Card* card){
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i] == card) {
            hand.erase(hand.begin() + i);
        }
    }
}

bool Player::hasValidMove(Card* topCard, Color currentColor){
    for (Card* card : hand) {
        if (topCard->get_Color() == currentColor) {
            return true;
        }
    }
    return false;
}

void Player::callUno(){
    hasCalledUno = true;
}

size_t Player::getHandSize(){
    return hand.size();
}