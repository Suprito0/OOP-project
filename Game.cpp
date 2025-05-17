#include"Game.h"
#include "Player.h"

void Game::initialize(int numPlayers, GameMode* mode){
    this->gameMode = mode;
    if (this->gameMode->getModeName() == "normal"){
        Player* player1 = new HumanPlayer();
        for(int i=0; i<numPlayers; i++){
        this->players.push_back();
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