#include "Deck.h"
#include "NumberCard.h"
#include "ActionCard.h"
#include "SpecialActionCard.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

Deck::Deck(){
    std::srand(std::time(0));  // Seed the random generator once in constructor
    initialize();
}

void Deck::initialize(){
    cards.clear();
    discardPile.clear();
    // UNO standard colors
    std::vector<Color> colors = {Red, Green, Blue, Yellow};
    // 1. Number Cards (0-9) 
    for (Color color : colors) {
        // One 0 per color
        cards.push_back(new NumberCard(color, 0));

        // Two of each 1-9 per color
        for (int i = 1; i <= 9; ++i) {
            cards.push_back(new NumberCard(color, i));
            cards.push_back(new NumberCard(color, i));
        }
    }
    // 2. Action Cards (Skip, Reverse, Draw Two) 
    for (Color color : colors) {
        for (int i = 0; i < 2; ++i) {
            cards.push_back(new ActionCard(color, Skip));
            cards.push_back(new ActionCard(color, Reverse));
            cards.push_back(new ActionCard(color, Draw_Two));
        }
    }
    // 3. Wild Cards 
    for (int i = 0; i < 4; ++i) {
        cards.push_back(new ActionCard(None, Wild));          // Wild
        cards.push_back(new ActionCard(None, Wild_Draw_Four));  // Wild Draw Four
    }
    // 4. SpecialActionCard 
    for (int i = 0; i < 4; ++i) {
        cards.push_back(new SpecialActionCard(None));
    }
    shuffle();
}

void Deck::shuffle(){
    for (size_t i = 0; i < cards.size(); ++i) {
        int j = i + rand() % (cards.size() - i);  // random index between i and end
        std::swap(cards[i], cards[j]);            // swap elements
    }
}

Card* Deck::drawCard() {
    if (cards.empty()) {
        reshuffleIfNeeded();  // Refill the deck from discard pile
    }

    //check after reshuffling attempt
    if (cards.empty()) {
        std::cout << "No cards left to draw!" << std::endl;
        return nullptr;
    }

    Card* top = cards.back();
    cards.pop_back();
    return top;
}

void Deck::addToDiscardPile(Card* card) {
    discardPile.push_back(card);
}

Card* Deck::get_TopDiscard() const {
    if (discardPile.empty()) return nullptr;
    return discardPile.back();
}

void Deck::reshuffleIfNeeded() {
    if (cards.empty() && discardPile.size() > 1) {
        Card* top = discardPile.back();  // Keep top discard
        discardPile.pop_back();  // Remove it temporarily

        // Move rest of discard pile back to deck
        cards = discardPile;
        discardPile.clear();
        discardPile.push_back(top);  // Keep top card on discard pile

        shuffle();
        std::cout << "Deck reshuffled from discard pile." << std::endl;
    }
}

int Deck::get_DeckSize() const {
    return cards.size();
}

int Deck::get_DiscardSize() const {
    return discardPile.size();
}

Deck::~Deck() {
    for (Card* card : cards) {
        delete card;
    }
    for (Card* card : discardPile) {
        delete card;
    }
}