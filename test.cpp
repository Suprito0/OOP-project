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
    Game game("Suprito", &mode);

    // cout << "Input your name:" << endl;
    // cin >> playerName;

    // game.getPlayer(0)->displayHand();
    // game.getPlayer(1)->displayHand();
    // game.getPlayer(2)->displayHand();
    // game.getPlayer(3)->displayHand();

    game.start();
    
}