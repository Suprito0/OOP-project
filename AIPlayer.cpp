#include "AIPlayer.h"

#include "ActionCard.h"
#include "Card.h"
#include "Deck.h"

AIPlayer::AIPlayer() {
  this->name = "Bot";
  this->isItHuman = false;
}
AIPlayer::AIPlayer(string name) : Player(name) { this->isItHuman = false; }

Card *AIPlayer::playTurn(Card *topCard, Color currentColor, Deck *decks) {
  if (!decks) {
    std::cerr << "[ERROR] Deck pointer is null!" << std::endl;
    return nullptr;
  }

  if (!topCard) {
    std::cerr << "[ERROR] Top card is null!" << std::endl;
    return nullptr;
  }

  cout << "Bot Selecting Card" << endl;
  Card *AICard = strategicCardSelection(topCard, currentColor);

  if (AICard != nullptr) {
    if (this->getHandSize() == 1) {
      cout << "Bot has called UNO" << endl;
      this->callUno(true);
    }
    decks->addToDiscardPile(AICard);
    removeCardFromHand(AICard);
    return AICard;
  }

  Card *newCard = decks->drawCard();
  if (newCard) {
    cout << "Bot drawing Card" << endl;
    addCardToHand(newCard);
  } else {
    return new ActionCard(None, Skip);
  }

  return nullptr;
}

Card *AIPlayer::strategicCardSelection(Card *topCard, Color currentColor) {
  for (Card *card : hand) {  // Chooses a wild if it has one
    if (card->canPlayOn(topCard) || card->get_Color() == currentColor) {
      return card;
    }
  }
  return nullptr;
}
