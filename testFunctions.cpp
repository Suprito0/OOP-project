#include <gtest/gtest.h>
#include "Game.h"
#include "HumanPlayer.h"
#include "SpecialActionCard.h"
#include "Deck.h"
#include "GameMode.h"
#include "Card.h"
#include <sstream>
#include <iostream>

TEST(GameTest, GameInitializationRealMode) {
    GameMode mode;
    Game game(&mode);
    EXPECT_FALSE(game.isGameOver());
}

TEST(HumanPlayerTest, ConstructorSetsIsHuman) {
    HumanPlayer player("test");
    EXPECT_TRUE(player.isHuman());
}

TEST(HumanPlayerTest, SetGameReference) {
    HumanPlayer player;
    GameMode mode;
    Game game(&mode);
    player.setGame(&game);
    SUCCEED(); // Nothing crashes
}

TEST(SpecialActionCardTest, ConstructorSetsDefaults) {
    SpecialActionCard card(Color::Red, ActionType::Skip);
    EXPECT_EQ(card.get_TargetPlayerIndex(), -1);
}

TEST(SpecialActionCardTest, ToStringFormat) {
    SpecialActionCard card(Color::Green, ActionType::Reverse);
    std::string out = card.toString();
    EXPECT_NE(out.find("Green"), std::string::npos);
    EXPECT_NE(out.find("Reverse"), std::string::npos);
}

// Main runner
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
