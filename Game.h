#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Enum.h"
using namespace std;

class Card;
class SpecialActionCard;
class Player;
class Deck;
class GameMode;

class Game
{
protected:
    vector<Player *> players;
    vector<SpecialActionCard*> specialCards;
    Deck *deck;
    GameMode *gameMode;
    Card *currentCard;
    int currentPlayerIndex;
    bool clockwise;
    Color currentColor;
    bool gameOver;
    int drawStack;

public:
    // void initialize(int numPlayers, GameMode* mode);
    // void initialize(string playerName, GameMode* mode);
    Game(string playerName, GameMode *mode);
    void setSpecialCards(SpecialActionCard* specialActionCard);
    void start();
    void nextTurn();
    bool isValidMove(Card *card);
    bool isClockwise();
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
    int getCurrentPlayerIndex();
    void updateCurrentCard(Card *card);
    bool isGameOver();
    vector<SpecialActionCard*>* getSpecialCards();
    void specialActionCheck();
    void endGame();

    void play();
    string colorToString(Color color);
};

#endif // GAME_H