#include"Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "GameMode.h"

void Game::initialize(string playerName, GameMode* mode){
    this->currentPlayerIndex = 0;
    this->gameMode = mode;
    this->isClockwise = true;
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
    this->deck->initialize();
    for(int i = 0; i < 7; i++){
        for (int j = 0; j < 4; j++){
            players[j]->addCardToHand(this->deck->drawCard());
        }
    }
    this->deck->addToDiscardPile(this->deck->drawCard());
    this->currentCard = this->deck->get_TopDiscard();
}
void Game::start(){
    int i = 0;
    while (i == 0){
        if (this->isClockwise){
            for(int j = this->currentPlayerIndex; j<4 ;j ++){
                players[j]->playTurn(this->currentCard, this->currentCard->get_Color(), this->deck);
                this->currentPlayerIndex++;
                if (checkForWinner()){
                    break;
                }
                if (this->currentPlayerIndex >= 4){
                    this->currentPlayerIndex = this->currentPlayerIndex - 4;
                }
                if (this->isClockwise == false){
                    break;
                }
            }
        } else {
            for (int j = this->currentPlayerIndex; j>=0; j--){
                players[j]->playTurn(this->currentCard, this->currentCard->get_Color(), this->deck);
                this->currentPlayerIndex--;
                if (checkForWinner()){
                    break;
                }
                if (this->currentPlayerIndex <=0){
                    this->currentPlayerIndex = this->currentPlayerIndex + 4;
                }
                if (this->isClockwise == false){
                    break;
                }
            }
        }
        if (checkForWinner()){
                    break;
        }
    }
    cout << this->players[this->currentPlayerIndex]->getName() << endl;
}
// void Game::nextTurn();
bool Game::isValidMove(Card* card){
    return card->canPlayOn(this->currentCard);
}
void Game::playCard(Card* card){
    this->deck->addToDiscardPile(card);
}
void Game::drawCard(){

}
bool Game::checkForWinner(){
    return (this->players[this->currentPlayerIndex]->getHandSize() == 0);
}
// void Game::handleSpecialCard(Card* card);
void Game::reverseDirection(){
    if(this->isClockwise){
        this->isClockwise = false;
    } else{
        this->isClockwise = true;
    }
}
void Game::skipNextPlayer(){
    this->currentPlayerIndex++;
}
void Game::forceDraw(int numCards){
    for (int i = 0; i < numCards; i++){
        this->players[this->currentPlayerIndex]->addCardToHand(this->deck->drawCard());
    }
}
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
// void Game::endGame();