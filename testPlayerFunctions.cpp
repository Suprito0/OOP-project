#include <gtest/gtest.h>
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "ActionCard.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"
#include "Deck.h"
#include "GameMode.h"
#include "Game.h"
#include <sstream>

   // Testing Player functions

class TestPlayer : public Player {   // TestPlayer class
    public:
        TestPlayer(std::string name) : Player(name){}
        Card* playTurn(Card* topCard, Color currentColor, Deck* decks) override {return nullptr;}
        ~TestPlayer() override {}
};

class TestPlayerSetUp : public ::testing::Test {   // Setting up new class for testing
    public:
        TestPlayer* Player1;
        Card* c1;
        Card* c2;
        Card* c3;
        Card* c4;
        Card* c5;

        void SetUp() {   // Initialise objects for testing
            Player1 = new TestPlayer("TestPlayer");
            c1 = new NumberCard(Red, 5);
            c2 = new NumberCard(Blue, 7);
            c3 = new ActionCard(Red, Reverse);
            c4 = new ActionCard(Blue, Reverse);
            c5 = new ActionCard(None, Wild);
        }

        void TearDown() {   // Delete dynamically allocated data
            delete Player1;
            delete c1;
            delete c2;
            delete c3;
            delete c4;
            delete c5;
        }
};

TEST_F(TestPlayerSetUp, checkIfHuman) {   // Checks if test player is human
    EXPECT_FALSE(Player1->isHuman());
}

TEST_F(TestPlayerSetUp, AddCardToHandIncreasesHandSize) {   // Checks if you can add cards to a player hand
    Player1->addCardToHand(c1);
    Player1->addCardToHand(c2);
    EXPECT_EQ(2, Player1->getHandSize());
}

TEST_F(TestPlayerSetUp, RemoveCardFromHandDecreasesHandSize) {   // Checks if you can remove cards from a player hand
    Player1->addCardToHand(c1);
    Player1->addCardToHand(c2);
    EXPECT_EQ(2, Player1->getHandSize());
    Player1->removeCardFromHand(c2);
    EXPECT_EQ(1, Player1->getHandSize());
}

TEST_F(TestPlayerSetUp, checkingUnoFunctions) {   // Checking if uno can be called
    EXPECT_FALSE(Player1->getUno());
    Player1->callUno(true);
    EXPECT_TRUE(Player1->getUno());
}

TEST_F(TestPlayerSetUp, returningCorrectName) {   // Checking if name can be retrieved
    EXPECT_EQ("TestPlayer", Player1->getName());
}

TEST_F(TestPlayerSetUp, checkingScoringFunction1) {   // Checking that scores are correctly returned
    Player1->addCardToHand(c1);
    Player1->addCardToHand(c3);
    EXPECT_EQ(25, Player1->calculateScore());
}

TEST_F(TestPlayerSetUp, checkingScoringFunction2) {
    Player1->addCardToHand(c1);
    Player1->addCardToHand(c5);
    EXPECT_EQ(45, Player1->calculateScore());
}