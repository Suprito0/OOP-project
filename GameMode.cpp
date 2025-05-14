#include"GameMode.h"

GameMode::GameMode(){
    this->modeName = "normal";
}
GameMode::GameMode(string modeName){
    this->modeName = modeName;
}
void GameMode::initialize(){
    if (modeName == "normal"){
        this->winningScore = NULL;
        this->allowStacking = false;
        this->gameModeDescription = "normal Uno rules with no stacking";
    } else if (modeName == "stacking") {
        this->winningScore = NULL;
        this->allowStacking = true;
        this->gameModeDescription = "normal Uno rules with stacking";
    } else{
        cout << "invalid Gamemode" << endl;
    }
}
int GameMode::calculateScore(vector<Card*> remainingCards){

}
string GameMode::getDescription(){
    return this->gameModeDescription;
}