#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"

AIPlayer::AIPlayer()
{
    this->name = "Bot";
    this->isItHuman = false;
}
AIPlayer::AIPlayer(string name) : Player(name) { this->isItHuman = false; }

// Card* AIPlayer::playTurn(Card* topCard, Color currentColor, Deck* decks){
//     Card* AICard = strategicCardSelection();

//     if (AICard != nullptr) {   // AI plays a wild card if it has one
//         decks->addToDiscardPile(AICard);
//         removeCardFromHand(AICard);
//         chooseOptimalColor();
//         return AICard;
//     } else {
//         if (hasValidMove(topCard, currentColor)) {   // Plays a valid card if it has one
//             for (Card* card : hand) {
//                 if (card->get_Color() == currentColor) {
//                     decks->addToDiscardPile(card);
//                     removeCardFromHand(card);
//                     return card;
//                 }
//             }
//         } else {   // Otherwise draws a card
//             Card* newCard = decks->drawCard();
//             addCardToHand(newCard);
//             return nullptr;
//         }
//     }
// }

Card *AIPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks)
{
    if (!decks)
    {
        std::cerr << "[ERROR] Deck pointer is null!" << std::endl;
        return nullptr;
    }

    if (!topCard)
    {
        std::cerr << "[ERROR] Top card is null!" << std::endl;
        return nullptr;
    }

    cout << "Bot Selecting Card" << endl;
    if (this->getHandSize() == 1)
    {
        cout << "Bot has called UNO" << endl;
        this->callUno(true);
    }
    Card *AICard = strategicCardSelection(topCard, currentColor);

    if (AICard != nullptr)
    {
        decks->addToDiscardPile(AICard);
        removeCardFromHand(AICard);
        // chooseOptimalColor();
        return AICard;
    }

    if (hasValidMove(topCard, currentColor))
    {
        for (Card *card : hand)
        {
            if (card && card->get_Color() == currentColor)
            {
                decks->addToDiscardPile(card);
                removeCardFromHand(card);
                return card;
            }
        }
    }

    Card *newCard = decks->drawCard();
    if (newCard)
    {
        cout << "Bot drawing Card" << endl;
        addCardToHand(newCard);
    }
    else
    {
        std::cerr << "[WARN] Tried to draw a card, but deck is empty!" << std::endl;
    }

    return nullptr;
}

Card *AIPlayer::strategicCardSelection(Card *topCard, Color currentColor)
{
    for (Card *card : hand)
    { // Chooses a wild if it has one
        if (card->canPlayOn(topCard) || card->get_Color() == currentColor)
        {
            return card;
        }
    }
    return nullptr;
}

// Color AIPlayer::chooseOptimalColor(){
//     int countRed, countGreen, countBlue, countYellow = 0;
//     Color currentColour;

//     for (Card* card : hand) {
//         currentColour = card->get_Color();
//         switch (currentColour) {
//             case Red:
//                 countRed++;
//                 break;
//             case Green:
//                 countGreen++;
//                 break;
//             case Blue:
//                 countBlue++;
//                 break;
//             case Yellow:
//                 countYellow++;
//                 break;
//             default:
//                 break;
//         }
//     }

//     Color optimalColour = Red;
//     int maxCount = countRed;

//     if (countGreen > maxCount) {
//         maxCount = countGreen;
//         optimalColour = Green;
//     }

//     if (countBlue > maxCount) {
//         maxCount = countBlue;
//         optimalColour = Blue;
//     }

//     if (countYellow > maxCount) {
//         maxCount = countYellow;
//         optimalColour = Yellow;
//     }

//     return optimalColour;
// }

// void AIPlayer::displayHand(){
//     int numCards = hand.size();
//         cout << this->getName() << " : " ;
//     for (size_t i = 0; i < numCards; i++) {
//         std::cout << "Card " << i+1 << " :" << hand[i]->get_ColorString() << " " << hand[i]->get_CardTypeString() << " | ";
//     }
//     std::cout << std::endl;
// }