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
        this->gameModeDescription = "Normal Uno rules with no stacking";
        this->numOfPlayers = 1;
    }
    else if (modeName == "stacking")
    {
        this->winningScore = 0;
        this->allowStacking = true;
        this->gameModeDescription = "Normal Uno rules with stacking";
        this->numOfPlayers = 1;
    }
    else if (modeName == "multiplayer") {
        this->winningScore = 0;
        this->allowStacking = false;
        this->gameModeDescription = "Normal Uno with multiple human player.";
        string inputString;
        while (true){
            cout << "How many players will be playing?" << endl;
            cin >> inputString;
            try
            {
                this->numOfPlayers = stoi(inputString);
                if (this->numOfPlayers >= 1 || this->numOfPlayers <= 4){
                    break;
                } else {
                    cout << "Invalid input. Please choose a number between 1 & 4." << endl;
                    continue;
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
        }
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
int GameMode::getNumOfPlayers(){
    return this->numOfPlayers;
}

GameMode::~GameMode(){
    
}