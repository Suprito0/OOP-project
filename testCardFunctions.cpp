#include <gtest/gtest.h>
#include "ActionCard.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"
#include "Enum.h"

   // Testing number cards

TEST(NumberCardTest, getColor) {   // Check if correct colour is retrieved
    NumberCard c1(Red, 5);
    EXPECT_EQ(Red, c1.get_Color());
}

TEST(NumberCardTest, getNumber) {   // Check if correct number is retrieved
    NumberCard c1(Blue, 3);
    EXPECT_EQ(3, c1.get_number());
}

TEST(NumberCardTest, PlayOnSameNumber) {   // Checking if same number cards can be played
    NumberCard c1(Red, 5);
    NumberCard c2(Blue, 5);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(NumberCardTest, PlayOnSameColour) {   // Checking if same colour cards can be played
    NumberCard c1(Red, 0);
    NumberCard c2(Red, 8);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(NumberCardTest, PlayOnDifferentNumberAndColour) {   // Checking if different number and colour cards can be played
    NumberCard c1(Red, 0);
    NumberCard c2(Yellow, 1);
    EXPECT_FALSE(c1.canPlayOn(&c2));
}

   // Testing action cards

TEST(ActionCardTest, getColor) {   // Check if correct colour is retrieved
    ActionCard c1(Red, Reverse);
    EXPECT_EQ(Red, c1.get_Color());
}

TEST(ActionCardTest, getAction) {   // Check if correct action is retrieved
    ActionCard c1(Yellow, Skip);
    EXPECT_EQ(Skip, c1.get_ActionType());
}

TEST(ActionCardTest, PlayOnSameColour) {   // Checking if same colour card can be played
    ActionCard c1(Red, Reverse);
    ActionCard c2(Red, Skip);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(ActionCardTest, PlayOnSameAction) {   // Checking if same type can be played
    ActionCard c1(Blue, Skip);
    ActionCard c2(Green, Skip);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(ActionCardTest, PlayOnDifferentColourAndType) {   // Checking if different colour and type can be played
    ActionCard c1(Red, Skip);
    ActionCard c2(Blue, Reverse);
    EXPECT_FALSE(c1.canPlayOn(&c2));
}

   // Testing wild cards

TEST(WildCardTest, checkColor) {   // Checking if wild returns correct colour
    ActionCard c1(None, Wild);
    EXPECT_EQ(None, c1.get_Color());
}

TEST(WildCardTest, checkActionType) {   // Checking if wild returns correct action
    ActionCard c1(None, Wild_Draw_Four);
    EXPECT_EQ(Wild_Draw_Four, c1.get_ActionType());
}

TEST(WildCardTest, PlayOnNumberCard) {   // Checking if wild can play on number card
    ActionCard c1(None, Wild);
    NumberCard c2(Green, 7);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(WildCardTest, PlayOnActionCard) {   // Checking if wild can play on action card
    ActionCard c1(None, Wild);
    ActionCard c2(Blue, Skip);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}

TEST(WildCardTest, PlayOnWildCard) {   // Checking if wild can play on wild
    ActionCard c1(None, Wild);
    ActionCard c2(None, Wild_Draw_Four);
    EXPECT_TRUE(c1.canPlayOn(&c2));
}