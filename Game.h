#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <regex>
#include <thread>

#include "Enum.h"
using namespace std;

class Card;
class ActionCard;
class SpecialActionCard;
class Player;
class Deck;
class GameMode;

class Game
{
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
    int tempPlayerIndex;
    Player *winner = nullptr;
    map<string, int> playerScores;
    bool gameError;
    bool willSkip;

public:
    Game(GameMode *mode);
    void setSpecialCards(SpecialActionCard *specialActionCard);
    void start();
    bool isValidMove(Card *card);
    bool isClockwise();
    bool checkForWinner();
    void reverseDirection();
    void skipPlayer();
    void forceDraw(int numCards);
    void setWillSkip(bool willSkip);
    void changeColor(Color newColor);
    Player *getCurrentPlayer();
    Player *getNextPlayer();
    Player *getPreviousPlayer();
    Player *getPlayer(int i);
    int getCurrentPlayerIndex();
    int getTempPlayerIndex();
    void setCurrentPlayerIndex(int index);
    void updateCurrentCard(Card *card);
    bool isGameOver();
    vector<SpecialActionCard *> *getSpecialCards();
    void specialActionCheck();
    void specialDraw(int numCards, int playerIndex);
    bool isFirstTurn();
    bool isGameError();
    void play();
    string colorToString(Color color);
    vector<Player *> getPlayers() const;
    string getWinnerName() const;
    void loadScores();
    void saveScores();
    void printScores();
    void updateScores(string winnerName);
    ~Game();
};

#endif // GAME_H