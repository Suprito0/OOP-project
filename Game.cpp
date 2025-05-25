#include "Game.h"

#include <chrono>
#include <thread>

#include "AIPlayer.h"
#include "Card.h"
#include "Deck.h"
#include "GameMode.h"
#include "HumanPlayer.h"

Game::Game(string playerName, GameMode *mode) {
  // cout << "Building Deck" << endl;
  this->deck = new Deck;

  this->currentPlayerIndex = 0;
  this->gameMode = mode;
  this->isClockwise = true;
  if (this->gameMode->getModeName() == "normal") {
    int botNum = 3;
    // cout << "Creating human player" << endl;
    Player *player1 = new HumanPlayer(playerName);
    ((HumanPlayer *)player1)
        ->setGame(this);  // Let the human player access game data
    this->players.push_back(player1);
    for (int i = 0; i < botNum; i++) {
      ostringstream botName;
      // cout << "Creating Bot " << i+1 << endl;
      botName << "Bot" << i + 1;
      players.push_back(new AIPlayer(botName.str()));
    }
  }

  // this->deck->initialize();
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      // cout << "Dealing Card " << i+1 << " to " << players[j]->getName() <<
      // endl;
      players[j]->addCardToHand(this->deck->drawCard());
    }
  }
  this->deck->addToDiscardPile(this->deck->drawCard());
  this->currentCard = this->deck->get_TopDiscard();

  for (Player* p : players) {
    playerScores[p->getName()] = 0;
  }

  loadScores();
}
void Game::start() {
  this->currentCard->play(this);
  this->currentColor = this->currentCard->get_Color();
  if (this->isClockwise == false) {
    this->currentPlayerIndex = 3;
  }

  while (true) {
    if (this->isClockwise) {
      while (true) {
        play();
        if (checkForWinner()) {
          break;
        }
        if (this->isClockwise == false) {
          this->currentPlayerIndex--;
          if (this->currentPlayerIndex < 0) {
            this->currentPlayerIndex = this->currentPlayerIndex + 4;
          }
          break;
        }
        this->currentPlayerIndex++;
        if (this->currentPlayerIndex >= 4) {
          this->currentPlayerIndex = this->currentPlayerIndex - 4;
        }
      }
    } else {
      while (true) {
        play();
        if (checkForWinner()) {
          break;
        }
        if (this->isClockwise == true) {
          this->currentPlayerIndex++;
          if (this->currentPlayerIndex >= 4) {
            this->currentPlayerIndex = this->currentPlayerIndex - 4;
          }
          break;
        }
        this->currentPlayerIndex--;
        if (this->currentPlayerIndex < 0) {
          this->currentPlayerIndex = this->currentPlayerIndex + 4;
        }
      }
    }
    if (checkForWinner()) {
      break;
    }
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
bool Game::isValidMove(Card *card) {
  return card->canPlayOn(this->currentCard);
}
void Game::playCard(Card *card) { this->deck->addToDiscardPile(card); }
void Game::drawCard() {}
bool Game::checkForWinner() {
  if (currentPlayerIndex < 0 || currentPlayerIndex >= players.size()) {
    std::cerr << "[ERROR] Invalid currentPlayerIndex: " << currentPlayerIndex
              << std::endl;
    return false;
  }
  Player *p = players[currentPlayerIndex];
  if (!p) {
    std::cerr << "[ERROR] Current player is nullptr." << std::endl;
    return false;
  }
  //   if (p->getUno()) {
  //     if (p->getHandSize() == 0) {
  //       cout << "UNO & 0 cards" << endl;
  //       this->winner = p; //set the winner
  //       return true;
  //     } else {
  //       cout << "UNO & non-zero cards" << endl;
  //       p->callUno(false);
  //       p->addCardToHand(this->deck->drawCard());
  //       p->addCardToHand(this->deck->drawCard());
  //       return false;
  //     }
  //   } else {
  //     if (p->getHandSize() == 0) {
  //       cout << "No UNO & 0 cards" << endl;
  //       p->addCardToHand(this->deck->drawCard());
  //       p->addCardToHand(this->deck->drawCard());
  //       return false;
  //     }
  //   }
  //   return false;
  //   ;
  int handSize = p->getHandSize();

  if (handSize == 0) {
    if (p->getUno()) {
      std::cout << "UNO & 0 cards\n";
      this->winner = p;
      string winnerName = p->getName();
      updateScores(winnerName);
      saveScores();
      printScores();
      isGameOver();
      return true;
    } else {
      std::cout << "No UNO & 0 cards\n";
      p->addCardToHand(this->deck->drawCard());
      p->addCardToHand(this->deck->drawCard());
      return false;
    }
  }

  // Reset UNO flag if hand size > 1 (player didn't play second-last card)
  if (handSize > 1 && p->getUno()) {
    p->callUno(false);
  }

  return false;
}

// void Game::handleSpecialCard(Card* card);
void Game::reverseDirection() {
  if (this->isClockwise) {
    this->isClockwise = false;
  } else {
    this->isClockwise = true;
  }
}
void Game::skipNextPlayer() {
  if (this->isClockwise) {
    this->currentPlayerIndex++;
    if (this->currentPlayerIndex >= 4) {
      this->currentPlayerIndex = this->currentPlayerIndex - 4;
    }
  } else {
    this->currentPlayerIndex--;
    if (this->currentPlayerIndex < 0) {
      this->currentPlayerIndex = this->currentPlayerIndex + 4;
    }
  }
}
void Game::forceDraw(int numCards) {
  for (int i = 0; i < numCards; i++) {
    this->getNextPlayer()->addCardToHand(this->deck->drawCard());
  }
}
void Game::changeColor(Color newColor) { this->currentColor = newColor; }

Player *Game::getPreviousPlayer() {
  int tempIndex = this->currentPlayerIndex;
  if (this->isClockwise) {
    tempIndex--;
    if (tempIndex < 0) {
      tempIndex = tempIndex + 4;
    }
    return this->players[tempIndex];
  } else {
    tempIndex++;
    if (tempIndex >= 4) {
      tempIndex = tempIndex - 4;
    }
    return this->players[tempIndex];
  }
}

Player *Game::getCurrentPlayer() {
  return this->players[this->currentPlayerIndex];
}
Player *Game::getNextPlayer() {
  int tempIndex = this->currentPlayerIndex;
  if (this->isClockwise) {
    tempIndex++;
    if (tempIndex >= 4) {
      tempIndex = tempIndex - 4;
    }
    return this->players[tempIndex];
  } else {
    tempIndex--;
    if (tempIndex < 0) {
      tempIndex = tempIndex + 4;
    }
    return this->players[tempIndex];
  }
}

Player *Game::getPlayer(int i) { return this->players[i]; }

void Game::updateCurrentCard(Card *card) { this->currentCard = card; }

bool Game::isGameOver() {
  for (auto& entry : playerScores) {
    if (entry.second >= 500) {
      std::cout << std::endl;
      std::cout << entry.first << " wins the game with " << entry.second << " points!" << std::endl;
      exit(0);
    }
  }
  return false;
}

void Game::play() {
  //   cout <<
  //   "--------------------------------------------------------------------"
  //           "--------------------------------------------------------------------"
  //           "-------------------------"
  //        << endl;
  //   cout << "Top Card: " << this->currentCard->get_ColorString() << " "
  //        << this->currentCard->get_CardTypeString() << " | ";

  //   cout << " Current player index " << this->currentPlayerIndex << " | ";
  //   cout << " Current Color " << this->currentCard->get_ColorString() <<
  //   endl;

  //   cout << players[this->currentPlayerIndex]->getName() << " PLAYING" <<
  //   endl;
  cout << "\n==================================================\n";
  cout << "               CURRENT GAME STATE\n";
  cout << "==================================================\n";
  cout << "Top Card:       " << this->currentCard->get_ColorString() << " "
       << this->currentCard->get_CardTypeString() << "\n";
  // cout << "Current Color:  " << this->currentCard->get_ColorString() << "\n";
  cout << "Current Color:  ";
  switch (this->currentColor) {
    case Red:
      cout << "Red\n";
      break;
    case Green:
      cout << "Green\n";
      break;
    case Blue:
      cout << "Blue\n";
      break;
    case Yellow:
      cout << "Yellow\n";
      break;
    default:
      cout << "None\n";
      break;
  }
  cout << "Current player index " << this->currentPlayerIndex << endl;
  cout << "Current Player: " << players[this->currentPlayerIndex]->getName()
       << "\n";
  cout << "==================================================\n";

  Card *playedCard = players[this->currentPlayerIndex]->playTurn(
      this->currentCard, this->currentColor, this->deck);
  if (playedCard != nullptr) {
    this->currentCard = playedCard;
    if (this->currentCard->get_Color() != None) {
      this->currentColor = this->currentCard->get_Color();
    }
    this->currentCard->play(this);
  }
}
// void Game::endGame();

vector<Player *> Game::getPlayers() const { return players; }

string Game::getWinnerName() const {
  return winner ? winner->getName() : "None";
}

void Game::loadScores() {   // Shows current log of players names' and their respective scores
  std::ifstream infile("scores.txt");

  if (!infile.is_open()) {
    std::cerr << "scores could not be found or opened; empty scoresheet." << std::endl;
    return;
  }

  std::string name;
  int score;

  while (infile >> name >> score) {
    playerScores[name] = score;
  }

  infile.close();
}

void Game::saveScores() {   // Overwrite score of the new winner
  std::ofstream outfile ("scores.txt");

  if (!outfile.is_open()) {
    std::cerr << "scores could not be opened or created; scores not saved." << std::endl;
  }

  for (auto& entry : playerScores) {
    outfile << entry.first << " " << entry.second << std::endl;
  }

  outfile.close();
}

void Game::printScores() {   // Displays current scoreboard
  std::cout << std::endl;
  std::cout << "========== CURRENT SCORES ==========" << std::endl;

  if (playerScores.empty()) {
    std::cout << "No scores recorded yet." << std::endl;
  } else {
    for (auto& entry : playerScores) {
      std::cout << "   " << entry.first << ": " << entry.second << " points" << std::endl;
    }
  }

  std::cout << "====================================" << std::endl;
}

void Game::updateScores(std::string winnerName) {
  int points = 0;

  for (Player* p : players) {
    if (p->getName() != winnerName) {
      points += p->calculateScore();
    }
  }

  playerScores[winnerName] += points;
  std::cout << winnerName << " gains " << points << " points this round!" << std::endl;
}

Game::~Game() {
  // Clean up dynamically allocated memory
  delete this->deck;  // Delete the deck object
  for (Player *player : players) {
    delete player;  // Delete each player object
  }
  players.clear();  // Clear the players vector
}