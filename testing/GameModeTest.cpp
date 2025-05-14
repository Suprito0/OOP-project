#include"../GameMode.h"

int main(){
    GameMode Game1("stacking");
    GameMode Game2;
    Game1.initialize();
    Game2.initialize();
    
    Game1.getAllowStacking();
    cout << Game1.getDescription() << endl;
    cout << Game1.getModeName() << endl;
    cout << Game1.getWinningScore() << endl;

    Game2.getAllowStacking();
    cout << Game2.getDescription() << endl;
    cout << Game2.getModeName() << endl;
    cout << Game2.getWinningScore() << endl;
}