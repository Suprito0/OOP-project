#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "GameMode.h"
#include "SpecialActionCard.h"

#include <thread>
#include <chrono>
#include <regex>

Game::Game(GameMode *mode)
{

    // cout << "Building Deck" << endl;
    this->deck = new Deck(this);

    this->gameOver = false;
    this->gameError = false;
    this->currentPlayerIndex = 0;
    this->gameMode = mode;
    this->clockwise = true;
    this->firstTurn = true;
    if (this->gameMode->getModeName() == "normal" || this->gameMode->getModeName() == "multiplayer" || this->gameMode->getModeName() == "simulation")
    {
        int playerNum = this->gameMode->getNumOfPlayers();
        int botNum = 4 - playerNum;

        for (int i = 0; i < playerNum; i++)
        {
            string playerName;
            while (true)
            {
                cout << "Enter the name of Player " << i + 1 << ": ";
                getline(cin >> ws, playerName); // read full line with leading whitespace trimmed

                // Reject if name contains escape sequences or is empty
                if (playerName.empty())
                {
                    cout << "Name cannot be empty. Try again.\n";
                    continue;
                }

                // Regex to allow only letters, numbers, and underscores (change as needed)
                if (!regex_match(playerName, regex("^[a-zA-Z0-9_]+$")))
                {
                    cout << "Name must contain only letters, numbers, or underscores. Try again.\n";
                    continue;
                }

                break; // valid name
            }

            players.push_back(new HumanPlayer(playerName));
            ((HumanPlayer *)players[i])->setGame(this); // Let the human player access game data
        }
        for (int i = 0; i < botNum; i++)
        {
            ostringstream botName;
            // cout << "Creating Bot " << i+1 << endl;
            botName << "Bot" << i + 1;
            players.push_back(new AIPlayer(botName.str()));
        }
        for (size_t i = 0; i < players.size(); i++)
        {
            // cout << "Assigning Index" << endl;
            players[i]->setIndex(i);
        }
    }

    // this->deck->initialize();
    for (int i = 0; i < 7; i++)
    {
        for (Player *player : players)
        {
            // cout << "Dealing Card " << i+1 << " to " << player->getName() << endl;
            player->addCardToHand(deck->drawCard());
        }
    }
    this->deck->addToDiscardPile(this->deck->drawCard());
    this->currentCard = this->deck->get_TopDiscard();
    // this->currentCard = new SpecialActionCard(Yellow, Skip);

    for (Player *p : players)
    {
        playerScores[p->getName()] = 0;
    }

    loadScores();
}

void Game::start()
{
    this->currentCard->play(this);

    if (!this->isClockwise())
        this->currentPlayerIndex = 3;

    while (true)
    {
        play();
        if (this->gameError)
        {
            cout << "===========GAME HAS BEEN TERMINATED===========\n";
            cout << "Reason: Draw deck is empty.\n";
            return;
        }

        if (checkForWinner())
        {
            break;
        }
        skipPlayer(); // changes currentPlayerIndex to the next player
        specialActionCheck();
    }

    std::cout << "\n==================================================\n";

    std::cout << "                   GAME OVER\n";

    std::cout << "==================================================\n";

    std::cout << "                    WINNER\n";

    std::cout << "--------------------------------------------------\n";

    std::cout << "                  " << this->winner->getName() << "\n";

    std::cout << "==================================================\n";
}

// void Game::nextTurn();
bool Game::isValidMove(Card *card)
{
    return card->canPlayOn(this->currentCard) || card->get_Color() == this->currentColor;
}
void Game::playCard(Card *card)
{
    this->deck->addToDiscardPile(card);
}
bool Game::isClockwise()
{
    return this->clockwise;
}

bool Game::checkForWinner()
{
    if (this->gameOver){ return true;}
    if (this->gameError)
    {
        return false;
    }

    if (currentPlayerIndex < 0 || currentPlayerIndex >= static_cast<int>(players.size()))
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
    int handSize = p->getHandSize();

    if (handSize == 0)
    {
        if (p->getUno())
        {
            std::cout << "UNO & 0 cards\n";
            this->winner = p;
            string winnerName = p->getName();
            updateScores(winnerName);
            saveScores();
            printScores();
            this->gameOver = true;
            return true;
        }
        else
        {
            std::cout << "No UNO & 0 cards\n";
            for (int i = 0; i < 2; i++)
            {
                Card *drawnCard = this->deck->drawCard();
                if (drawnCard)
                {
                    p->addCardToHand(drawnCard);
                }
                else
                {
                    this->gameError = true;
                }
            }
            return false;
        }
    }

    // Reset UNO flag if hand size > 1 (player didn't play second-last card)
    if (handSize > 1 && p->getUno())
    {
        cout << "You called UNO but you have more than 1 card. Drawing 2 Cards\n";
        for (int i = 0; i < 2; i++)
        {
            Card *drawnCard = this->deck->drawCard();
            if (drawnCard)
            {
                p->addCardToHand(drawnCard);
            } else {
                
                this->gameError = true;
            }
        }
        p->callUno(false);
    }

    return false;
}
void Game::reverseDirection()
{
    this->clockwise = !this->clockwise;
}
void Game::skipPlayer()
{
    int numPlayers = 4;
    int direction = this->isClockwise() ? 1 : -1;

    this->currentPlayerIndex = (this->currentPlayerIndex + direction + numPlayers) % numPlayers;
}
void Game::forceDraw(int numCards)
{
    Card *drawnCard = this->deck->drawCard();
    if (!drawnCard)
    {
        this->gameError = true;
        return;
    }
    for (int i = 0; i < numCards; i++)
    {
        this->getNextPlayer()->addCardToHand(drawnCard);
    }
}
void Game::specialDraw(int numCards)
{
    Card *drawnCard = this->deck->drawCard();
    if (!drawnCard)
    {
        this->gameError = true;
        return;
    }
    for (int i = 0; i < numCards; i++)
    {
        this->getCurrentPlayer()->addCardToHand(drawnCard);
    }
}

void Game::changeColor(Color newColor)
{
    this->currentColor = newColor;
}

Player *Game::getPreviousPlayer()
{
    int numPlayers = 4;
    int direction = this->isClockwise() ? -1 : 1;

    int prevIndex = (currentPlayerIndex + direction + numPlayers) % numPlayers;
    return players[prevIndex];
}

Player *Game::getCurrentPlayer()
{
    return this->players[this->currentPlayerIndex];
}

Player *Game::getNextPlayer()
{
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
    if (this->gameError)
    {
        return;
    }

    if (!this->gameMode->getIsFast())
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << "\n==================================================\n";
    cout << "               CURRENT GAME STATE\n";
    cout << "==================================================\n";
    if (this->currentCard->get_CardType() == Special_Action)
    {
        cout << "Top Card:       " << this->currentCard->get_ColorString() << "Special " << this->currentCard->get_ActionTypeString() << "\n";
    }
    else
    {
        cout << "Top Card:       " << this->currentCard->get_ColorString() << this->currentCard->get_ActionTypeString() << "\n";
    }
    cout << "Current Color:  " << colorToString(this->currentColor) << endl;
    cout << "Current player index " << this->currentPlayerIndex << endl;
    cout << "Current Player: " << players[this->currentPlayerIndex]->getName()
         << "\n";
    cout << "No. of Cards :      " << this->getCurrentPlayer()->getHandSize() << endl;
    cout << "Direction: " << (this->clockwise ? "Clockwise" : "Anti-Clockwise") << endl;
    cout << "==================================================\n";

    if (!this->gameMode->getIsFast())
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    Card *playedCard = this->getCurrentPlayer()->playTurn(this->currentCard, this->currentColor, this->deck);

    if (playedCard != nullptr)
    {
        if (playedCard->get_ActionType() == Skip && playedCard->get_Color() == None)
        {
            this->gameError = true;
            delete playedCard;
            return;
        }
        this->currentCard = playedCard;
        if (this->currentCard->get_Color() != None)
        {
            this->currentColor = this->currentCard->get_Color();
        }
        this->currentCard->play(this);
    }
}

int Game::getCurrentPlayerIndex()
{
    return this->currentPlayerIndex;
}

string Game::colorToString(Color color)
{
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

void Game::setSpecialCards(SpecialActionCard *specialActionCard)
{
    specialCards.push_back(specialActionCard);
}

vector<SpecialActionCard *> *Game::getSpecialCards()
{
    return &this->specialCards;
}

void Game::specialActionCheck()
{
    if (this->gameError)
    {
        return;
    }

    bool skip = false, reverse = false, cardIsCurrent = false;
    Player *currentPlayer = this->getCurrentPlayer();

    if (!currentPlayer)
    {
        std::cerr << "[ERROR] currentPlayer is nullptr in specialActionCheck." << std::endl;
        return;
    }

    for (SpecialActionCard *card : this->specialCards)
    {
        if (!card)
        {
            std::cerr << "[WARNING] Found nullptr in specialCards vector.\n";
            continue;
        }

        if (card->get_TargetPlayerIndex() == currentPlayer->getIndex())
        {
            if (card->get_ActionType() == Skip || card->get_ActionType() == Draw_Two)
            {
                skip = true;
                std::cout << "Special Skip " << skip << std::endl;
            }
            else if (card->get_ActionType() == Reverse)
            {
                reverse = !reverse;
                std::cout << "Special reverse " << reverse << std::endl;
            }

            if (card == this->currentCard)
            {
                cardIsCurrent = true;
                std::cout << "Special Card " << cardIsCurrent << std::endl;
            }

            card->specialAction(this);
        }
    }

    if (reverse)
    {
        this->skipPlayer();
    }
    else if (skip &&
             ((this->currentCard->get_ActionType() != Skip &&
               this->currentCard->get_ActionType() != Draw_Two &&
               this->currentCard->get_ActionType() != Wild_Draw_Four) ||
              cardIsCurrent))
    {
        this->skipPlayer();
        std::cout << "Special Skip game.cpp" << std::endl;
    }
}

vector<Player *> Game::getPlayers() const { return players; }

string Game::getWinnerName() const
{
    return winner ? winner->getName() : "None";
}

bool Game::isFirstTurn()
{
    bool temp = this->firstTurn;
    this->firstTurn = false;
    return temp;
}

void Game::setCurrentPlayerIndex(int index)
{
    this->currentPlayerIndex = index;
}

bool Game::isGameError()
{
    return this->gameError;
}

void Game::loadScores()
{ // Shows current log of players names' and their respective scores
    std::ifstream infile("scores.txt");

    if (!infile.is_open())
    {
        std::cerr << "scores could not be found or opened; empty scoresheet." << std::endl;
        return;
    }

    std::string name;
    int score;

    while (infile >> name >> score)
    {
        playerScores[name] = score;
    }

    infile.close();
}

void Game::saveScores()
{ // Overwrite score of the new winner
    std::ofstream outfile("scores.txt");

    if (!outfile.is_open())
    {
        std::cerr << "scores could not be opened or created; scores not saved." << std::endl;
    }

    for (auto &entry : playerScores)
    {
        outfile << entry.first << " " << entry.second << std::endl;
    }

    outfile.close();
}

void Game::printScores()
{ // Displays current scoreboard
    std::cout << std::endl;
    std::cout << "========== SCOREBOARD ==========" << std::endl;

    if (playerScores.empty())
    {
        std::cout << "No scores recorded yet." << std::endl;
    }
    else
    {
        for (auto &entry : playerScores)
        {
            std::cout << "   " << entry.first << ": " << entry.second << " points" << std::endl;
        }
    }

    std::cout << "====================================" << std::endl;
}

void Game::updateScores(std::string winnerName)
{
    int points = 0;

    for (Player *p : players)
    {
        if (p->getName() != winnerName)
        {
            points += p->calculateScore();
        }
    }

    playerScores[winnerName] += points;
    std::cout << winnerName << " gains " << points << " points this round!" << std::endl;
}

Game::~Game()
{
    // Clean up dynamically allocated memory
    delete this->deck; // Delete the deck object
    for (Player *player : players)
    {
        delete player; // Delete each player object
    }
    players.clear(); // Clear the players vector
}