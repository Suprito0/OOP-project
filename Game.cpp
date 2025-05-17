#include"Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

void Game::initialize(string playerName, GameMode* mode){
    this->gameMode = mode;
    if (this->gameMode->getModeName() == "normal"){
        int botNum = 3;
        string playerName;
        cout << "Enter your name: " << endl;
        cin >> playerName;
        Player* player1 = new HumanPlayer(playerName);
        this->players.push_back(player1);
        for(int i=0; i<botNum; i++){
            ostringstream botName;
            botName << "Bot" << i+1;
            players[i+1] = new AIPlayer(botName.str());
        }
    }
}
void Game::start(){

}
void Game::nextTurn();
bool Game::isValidMove(Card* card){
   
}
void Game::playCard(Card* card);
void Game::drawCard();
bool Game::checkForWinner();
void Game::handleSpecialCard(Card* card);
void Game::reverseDirection();
void Game::skipNextPlayer();
void Game::forceDraw(int numCards);
void Game::changeColor(Color newColor){
    this->currentColor = newColor;
}
// Player* Game::getCurrentPlayer();
// Player* Game::getNextPlayer();
void Game::updateCurrentCard(Card* card){
    this->currentCard = card;
}

bool Game::isGameOver(){
    return this->gameOver;
}
void Game::endGame();