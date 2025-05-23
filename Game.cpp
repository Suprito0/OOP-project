#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "GameMode.h"
#include "SpecialActionCard.h"

#include <thread>
#include <chrono>

Game::Game(string playerName, GameMode *mode)
{

    // cout << "Building Deck" << endl;
    this->deck = new Deck(this);

    this->currentPlayerIndex = 0;
    this->gameMode = mode;
    this->clockwise = true;
    if (this->gameMode->getModeName() == "normal")
    {
        int botNum = 3;
        // cout << "Creating human player" << endl;
        Player *player1 = new HumanPlayer(playerName);
        this->players.push_back(player1);
        for (int i = 0; i < botNum; i++)
        {
            ostringstream botName;
            // cout << "Creating Bot " << i+1 << endl;
            botName << "Bot" << i + 1;
            players.push_back(new AIPlayer(botName.str()));
        }
        for (int i = 0; i<players.size(); i++){
            players[i]->setIndex(i);
        }
    }

    // this->deck->initialize();
    for (int i = 0; i < 7; i++)
    {
        for (Player* player : players)
        {
            // cout << "Dealing Card " << i+1 << " to " << player->getName() << endl;
            player->addCardToHand(deck->drawCard());
        }
    }
    this->deck->addToDiscardPile(this->deck->drawCard());
    this->currentCard = this->deck->get_TopDiscard();
}

void Game::start()
{
    this->currentCard->play(this);

    if (!this->isClockwise())
        this->currentPlayerIndex = 3;

    while (!checkForWinner())
    {
        play();

        if (checkForWinner())
            break;

        specialActionCheck();
        skipNextPlayer(); // changes currentPlayerIndex to the next player
    }

    cout << "WINNER ----------------------------------------------------- "
              << this->getCurrentPlayer()->getName()
              << " ------------------------------------------" << endl;
}

// void Game::nextTurn();
bool Game::isValidMove(Card *card)
{
    return card->canPlayOn(this->currentCard);
}
void Game::playCard(Card *card)
{
    this->deck->addToDiscardPile(card);
}
void Game::drawCard()
{
}

bool Game::isClockwise(){
    return this->clockwise;
}

bool Game::checkForWinner()
{
    if (currentPlayerIndex < 0 || currentPlayerIndex >= players.size())
    {
        std::cerr << "[ERROR] Invalid currentPlayerIndex: " << currentPlayerIndex << std::endl;
        return false;
    }
    Player *p = players[currentPlayerIndex];
    if (!p)
    {
        std::cerr << "[ERROR] Current player is nullptr." << std::endl;
        return false;
    }
    if (p->getUno())
    {
        if (p->getHandSize() == 0)
        {
            cout << "UNO & 0 cards" << endl;
            return true;
        }
        else
        {
            cout << "UNO & non-zero cards" << endl;
            p->callUno(false);
            p->addCardToHand(this->deck->drawCard());
            p->addCardToHand(this->deck->drawCard());
            return false;
        }
    }
    else
    {
        if (p->getHandSize() == 0)
        {
            cout << "No UNO & 0 cards" << endl;
            p->addCardToHand(this->deck->drawCard());
            p->addCardToHand(this->deck->drawCard());
            return false;
        }
    }
    return false;
    ;
}
// void Game::handleSpecialCard(Card* card);
void Game::reverseDirection()
{
    this->clockwise = !this->clockwise;
}
void Game::skipNextPlayer()
{
    int numPlayers = 4; 
    int direction = this->isClockwise() ? 1 : -1;

    this->currentPlayerIndex = (this->currentPlayerIndex + direction + numPlayers) % numPlayers;

}
void Game::forceDraw(int numCards)
{
    for (int i = 0; i < numCards; i++)
    {
        this->getNextPlayer()->addCardToHand(this->deck->drawCard());
    }
}
void Game::changeColor(Color newColor)
{
    this->currentColor = newColor;
}

Player* Game::getPreviousPlayer() {
    int numPlayers = 4; 
    int direction = this->isClockwise() ? -1 : 1;

    int prevIndex = (currentPlayerIndex + direction + numPlayers) % numPlayers;
    return players[prevIndex];
}


Player *Game::getCurrentPlayer()
{
    return this->players[this->currentPlayerIndex];
}

Player* Game::getNextPlayer() {
    int numPlayers = 4; 
    int direction = this->isClockwise() ? 1 : -1;

    int nextIndex = (currentPlayerIndex + direction + numPlayers) % numPlayers;
    return players[nextIndex];
}


Player *Game::getPlayer(int i)
{
    return this->players[i];
}

void Game::updateCurrentCard(Card *card)
{
    this->currentCard = card;
}

bool Game::isGameOver()
{
    return this->gameOver;
}

void Game::play()
{
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Top Card: " << this->currentCard->get_ColorString() << " " << this->currentCard->get_CardTypeString() << " | ";

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    cout << " Current player index: " << this->currentPlayerIndex << " | ";
    cout << " Current Color: " << colorToString(this->currentColor) << " | ";
    cout << " No. of Cards: " << this->getCurrentPlayer()->getHandSize() << " | ";

    cout << this->getCurrentPlayer()->getName() << " PLAYING" << endl;

    Card *playedCard = this->getCurrentPlayer()->playTurn(this->currentCard, this->currentColor, this->deck);
    if (playedCard != nullptr)
    {
        this->currentCard = playedCard;
        if (this->currentCard->get_Color() != None)
        {
            this->currentColor = this->currentCard->get_Color();
        }
        this->currentCard->play(this);
    }
}

int Game::getCurrentPlayerIndex(){
    return this->currentPlayerIndex;
}

string Game::colorToString(Color color){
switch (color)
  {
  case Red:
    return "Red ";
  case Green:
    return "Green ";
  case Blue:
    return "Blue ";
  case Yellow:
    return "Yellow ";
  case None:
    return "None";
  default:
    return "Unknown ";
  }
}

void Game::setSpecialCards(SpecialActionCard* specialActionCard){
    specialCards.push_back(specialActionCard);
}

vector<SpecialActionCard*>* Game::getSpecialCards(){
    return &this->specialCards;
}

void Game::specialActionCheck() {
    bool skip = false;
    for (SpecialActionCard* card : this->specialCards){
        card->specialAction(this);
        if (card->get_TargetPlayerIndex() != 0 && (card->get_ActionType() == Skip || card->get_ActionType() == Draw_Two)){
            skip = true;
        }
    }
    if (skip) { this->skipNextPlayer(); }
}
// void Game::endGame();