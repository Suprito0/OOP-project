#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "GameMode.h"
#include "SpecialActionCard.h"

#include <thread>
#include <chrono>

Game::Game(GameMode *mode)
{

    // cout << "Building Deck" << endl;
    this->deck = new Deck(this);

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
            cout << "Enter the name of Player " << i + 1 << endl;
            cin >> playerName;
            // cout << "Creating human player" << endl;
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

        if (checkForWinner())
        {
            break;
        }
        skipPlayer(); // changes currentPlayerIndex to the next player
        specialActionCheck();
    }

    //   cout << "WINNER----------------------------------------------------- "

    //        << this->winner->getName()

    //        << "------------------------------------------" << endl;

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
    return card->canPlayOn(this->currentCard);
}
void Game::playCard(Card *card)
{
    this->deck->addToDiscardPile(card);
}
void Game::drawCard()
{
}

bool Game::isClockwise()
{
    return this->clockwise;
}

bool Game::checkForWinner()
{
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
            isGameOver();
            return true;
        }
        else
        {
            std::cout << "No UNO & 0 cards\n";
            p->addCardToHand(this->deck->drawCard());
            p->addCardToHand(this->deck->drawCard());
            return false;
        }
    }

    // Reset UNO flag if hand size > 1 (player didn't play second-last card)
    if (handSize > 1 && p->getUno())
    {
        cout << "You called UNO but you have more than 1 card. Drawing 2 Cards\n";
        p->addCardToHand(this->deck->drawCard());
        p->addCardToHand(this->deck->drawCard());
        p->callUno(false);
    }

    return false;
}
// void Game::handleSpecialCard(Card* card);
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
    for (int i = 0; i < numCards; i++)
    {
        this->getNextPlayer()->addCardToHand(this->deck->drawCard());
    }
}
void Game::specialDraw(int numCards)
{
    for (int i = 0; i < numCards; i++)
    {
        this->getCurrentPlayer()->addCardToHand(this->deck->drawCard());
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

    // cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    // cout << "Top Card: " << this->currentCard->get_ColorString() << " " << this->currentCard->get_CardTypeString() << " | ";

    // // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // cout << " Current player index: " << this->currentPlayerIndex << " | ";
    // cout << " Current Color: " << colorToString(this->currentColor) << " | ";
    // cout << " No. of Cards: " << this->getCurrentPlayer()->getHandSize() << " | ";
    // cout << " isClockwise: " << this->clockwise << " | ";

    // cout << this->getCurrentPlayer()->getName() << " PLAYING" << endl;

    cout << "\n==================================================\n";
    cout << "               CURRENT GAME STATE\n";
    cout << "==================================================\n";
    cout << "Top Card:       " << this->currentCard->get_ColorString() << this->currentCard->get_ActionTypeString() << "\n";
    // cout << "Current Color:  " << this->currentCard->get_ColorString() << "\n";
    cout << "Current Color:  " << colorToString(this->currentColor) << endl;
    cout << "Current player index " << this->currentPlayerIndex << endl;
    cout << "Current Player: " << players[this->currentPlayerIndex]->getName()
         << "\n";
    cout << "Direction: " << (this->clockwise ? "Clockwise" : "Anti-Clockwise") << endl;
    cout << "==================================================\n";

    // this_thread::sleep_for(std::chrono::milliseconds(2000));

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
    bool skip = false, reverse = false, cardIsCurrent = false;
    Player* currentPlayer = this->getCurrentPlayer();

    if (!currentPlayer) {
        std::cerr << "[ERROR] currentPlayer is nullptr in specialActionCheck." << std::endl;
        return;
    }

    for (SpecialActionCard *card : this->specialCards)
    {
        if (!card) {
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
                reverse = true;
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

void Game::setCurrentPlayerIndex(int index){
    this->currentPlayerIndex = index;
}
// void Game::firstActionPlay(ActionCard* card){

//   std::cout << "Played Action Card: " << card->toString() << " | " << endl;

//   switch (card->get_ActionType())
//   {
//   case Skip:
//     cout << " Skipping " << endl;
//     this->skipPlayer();
//     cout << " Skipped " << endl;
//     break;
//   case Reverse:
//     cout << " Reversing " << endl;
//     this->reverseDirection();
//     cout << " Reversed " << endl;
//     break;
//   case Draw_Two:
//     this->specialDraw(2);
//     this->skipPlayer(); // Next player misses turn
//     break;
//   case Wild:
//   case Wild_Draw_Four:
//     bool isHuman = this->getCurrentPlayer()->isHuman();
//     if (card->get_ActionType() == Wild_Draw_Four)
//     {
//       cout << "-----------force draw------------" << endl;
//       this->specialDraw(4);
//       cout << "-----------skipping------------" << endl;
//       this->skipPlayer();
//     }

//     if (isHuman)
//     {
//       // Ask player to choose a color
//       int choice = -1;
//       string choiceString;

//       std::cout << "Choose a color:\n";

//       while (true)
//       {
//         std::cout << "1. Red\n2. Green\n3. Blue\n4. Yellow\n> ";
//         std::cin >> choiceString;

//         if (choiceString == "1")
//         {
//           choice = 0;
//           break;
//         }
//         else if (choiceString == "2")
//         {
//           choice = 1;
//           break;
//         }
//         else if (choiceString == "3")
//         {
//           choice = 2;
//           break;
//         }
//         else if (choiceString == "4")
//         {
//           choice = 3;
//           break;
//         }
//         else
//         {
//           std::cout
//               << "Invalid choice. Please enter a number between 1 and 4.\n";
//         }
//       }
//       this->changeColor(static_cast<Color>(choice));

//       // Show color confirmation
//       switch (choice)
//       {
//       case 0:
//         std::cout << "Color changed to Red.\n";
//         break;
//       case 1:
//         std::cout << "Color changed to Green.\n";
//         break;
//       case 2:
//         std::cout << "Color changed to Blue.\n";
//         break;
//       case 3:
//         std::cout << "Color changed to Yellow.\n";
//         break;
//       default:
//         std::cout << "Invalid choice.\n";
//         break;
//       }

//       break;
//     }
//     else
//     {
//       Color choice = this->getCurrentPlayer()->chooseOptimalColor();
//       this->changeColor(choice);
//       switch (choice)
//       {
//       case Red:
//         std::cout << "Color changed to Red.\n";
//         break;
//       case Green:
//         std::cout << "Color changed to Green.\n";
//         break;
//       case Blue:
//         std::cout << "Color changed to Blue.\n";
//         break;
//       case Yellow:
//         std::cout << "Color changed to Yellow.\n";
//         break;
//       default:
//         std::cout << "Invalid choice.\n";
//         break;
//       }

//       break;
//     }
//   }

//   this->updateCurrentCard(card); // Set this card as top card
// }

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
    // // Delete all players
    // for (Player* player : players) {
    //     delete player;
    // }
    // players.clear();

    // // Delete all special cards if Game owns them
    // for (SpecialActionCard* card : specialCards) {
    //     delete card;
    // }
    // specialCards.clear();

    // // // Delete the deck
    // // delete deck;
    // // deck = nullptr;

    // // Only delete gameMode if Game owns it
    // delete gameMode;
    // gameMode = nullptr;

    // // Delete the current card (if it’s not managed by the deck)
    // delete currentCard;
    // currentCard = nullptr;

    // winner = nullptr;
}

// void Game::endGame();