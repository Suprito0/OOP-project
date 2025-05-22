#include "GameMode.h"
#include "Card.h"

GameMode::GameMode()
{
    this->modeName = "normal";
}
GameMode::GameMode(string modeName)
{
    this->modeName = modeName;
}
void GameMode::initialize()
{
    if (modeName == "normal")
    {
        this->winningScore = 0;
        this->allowStacking = false;
        this->gameModeDescription = "normal Uno rules with no stacking";
    }
    else if (modeName == "stacking")
    {
        this->winningScore = 0;
        this->allowStacking = true;
        this->gameModeDescription = "normal Uno rules with stacking";
    }
    else
    {
        cout << "invalid Gamemode" << endl;
    }
}
size_t GameMode::calculateScore(vector<Card *> remainingCards)
{
    int score = 0;
    size_t numOfRemainingCards = remainingCards.size();
    return numOfRemainingCards;
}
string GameMode::getDescription()
{
    return this->gameModeDescription;
}

string GameMode::getModeName()
{
    return this->modeName;
}
int GameMode::getWinningScore()
{
    return this->winningScore;
}
void GameMode::getAllowStacking()
{
    if (this->allowStacking == false)
    {
        cout << "stacking is not allowed" << endl;
    }
    else
    {
        cout << "stacking is allowed" << endl;
    }
}