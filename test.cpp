#include "Game.h"

int main(){
    Game* game;
    GameMode mode;

    string playerName;
    cout << "Input your name:" << endl;
    cin >> playerName;

    game->initialize(playerName, &mode);
    game->start();
}