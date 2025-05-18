#include "Game.h"
#include "SpecialActionCard.h"
#include "GameMode.h"
#include "NumberCard.h"
#include "AIPlayer.h"
#include "HumanPlayer.h"
#include "Deck.h"


int main(){
    Game* game;
    GameMode mode;

    string playerName;
    cout << "Input your name:" << endl;
    cin >> playerName;

    game->initialize(playerName, &mode);
    game->start();
}