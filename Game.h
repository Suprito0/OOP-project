#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Enum.h"
using namespace std;

class Card;
class ActionCard;
class SpecialActionCard;
class Player;
class Deck;
class GameMode;

class Game {
 protected:
  vector<Player *> players;
  vector<SpecialActionCard *> specialCards;
  Deck *deck;
  GameMode *gameMode;
  Card *currentCard;
  int currentPlayerIndex;
  bool clockwise;
  Color currentColor;
  bool gameOver;
  bool firstTurn;
  int drawStack;
  Player *winner = nullptr;
  map<string, int> playerScores;
  bool gameError;

 public:
  Game(GameMode *mode);
  void setSpecialCards(SpecialActionCard *specialActionCard);
  void start();
  void nextTurn();
  bool isValidMove(Card *card);
  bool isClockwise();
  void playCard(Card *card);
  void drawCard();
  bool checkForWinner();
  void handleSpecialCard(Card *card);
  void reverseDirection();
  void skipPlayer();
  void forceDraw(int numCards);
  void changeColor(Color newColor);
  Player *getCurrentPlayer();
  Player *getNextPlayer();
  Player *getPreviousPlayer();
  Player *getPlayer(int i);
  int getCurrentPlayerIndex();
  void setCurrentPlayerIndex(int index);
  void updateCurrentCard(Card *card);
  bool isGameOver();
  vector<SpecialActionCard *> *getSpecialCards();
  void specialActionCheck();
  void endGame();
  void specialDraw(int numCards);
  bool isFirstTurn();
  bool isGameError();
  void play();
  void firstActionPlay(ActionCard *card);
  string colorToString(Color color);
  vector<Player *> getPlayers() const;
  string getWinnerName() const;
  void loadScores();
  void saveScores();
  void printScores();
  void updateScores(std::string winnerName);
  ~Game();
};

#endif  // GAME_H