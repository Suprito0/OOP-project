#include "AIPlayer.h"

#include "ActionCard.h"
#include "Card.h"
#include "Deck.h"

AIPlayer::AIPlayer()
{
    this->name = "Bot";
    this->isItHuman = false;
}
AIPlayer::AIPlayer(string name) : Player(name) { this->isItHuman = false; }

Card *AIPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks)
{
    if (!decks)
    {
        cerr << "[ERROR] Deck pointer is null!" << endl;
        return nullptr;
    }

    if (!topCard)
    {
        cerr << "[ERROR] Top card is null!" << endl;
        return nullptr;
    }

    cout << this->getName() << " is selecting..." << endl;
    Card *AICard = strategicCardSelection(topCard, currentColor);

    if (AICard != nullptr)
    {
        if (this->getHandSize() == 1)
        {
            cout << this->getName() << " has called UNO" << endl;
            this->callUno(true);
        }
        cout << this->getName() << " is playing a card" << endl;
        decks->addToDiscardPile(AICard);
        removeCardFromHand(AICard);
        return AICard;
    }

    Card *newCard = decks->drawCard();
    if (newCard)
    {
        cout << this->getName() << " is drawing a card" << endl;
        addCardToHand(newCard);
    }
    else
    {
        return new ActionCard(None, Skip);
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