#include "Game.h"
#include "SpecialActionCard.h"
#include "GameMode.h"
#include "NumberCard.h"
#include "AIPlayer.h"
#include "HumanPlayer.h"
#include "Deck.h"


int main(){
    GameMode mode;
    cout << mode.getModeName() <<endl;
    Game game("suprito", &mode);

    // cout << "Input your name:" << endl;
    // cin >> playerName;

    game.start();
}