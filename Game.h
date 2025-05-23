#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Enum.h"
using namespace std;

class Card;
class Player;
class Deck;
class GameMode;

class Game
{
protected:
    vector<Player *> players;
    Deck *deck;
    GameMode *gameMode;
    Card *currentCard;
    int currentPlayerIndex;
    bool isClockwise;
    Color currentColor;
    bool gameOver;
    int drawStack;
    Player* winner = nullptr;

public:
    // void initialize(int numPlayers, GameMode* mode);
    // void initialize(string playerName, GameMode* mode);
    Game(string playerName, GameMode *mode);
    void start();
    void nextTurn();
    bool isValidMove(Card *card);
    void playCard(Card *card);
    void drawCard();
    bool checkForWinner();
    void handleSpecialCard(Card *card);
    void reverseDirection();
    void skipNextPlayer();
    void forceDraw(int numCards);
    void changeColor(Color newColor);
    Player *getCurrentPlayer();
    Player *getNextPlayer();
    Player *getPreviousPlayer();
    Player *getPlayer(int i);
    void updateCurrentCard(Card *card);
    bool isGameOver();
    void endGame();
    void play();
    vector<Player*> getPlayers() const;
    string getWinnerName() const;
    ~Game();
};

#endif // GAME_H