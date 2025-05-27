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
    vector<Player *> players;                 // stores the pointers to the Player objects
    vector<SpecialActionCard *> specialCards; // stores the pointers to the SpecialActionCard objects
    Deck *deck;                               // stores the pointer to the Deck object
    GameMode *gameMode;                       // stores the ponter to the GameMode object
    Card *currentCard;                        // stores the ponter to the Card object that is currently in play
    int currentPlayerIndex;                   // stores the index of the player currently playing
    bool clockwise;                           // stores the direction of the turns (true - ascending index, false - descending index)
    Color currentColor;                       // stores the color of the play
    bool gameOver;                            // indicates if the game if over or not
    bool firstTurn;                           // indication of the first turn
    int tempPlayerIndex;                      // stores a player's index temporarily which is needed in the function specialActionCheck
    Player *winner;                           // stores the Player object who won
    map<string, int> playerScores;            // stores the scores of the players
    bool gameError;                           // indicates if there the draw pile is empty or not
    bool willSkip;                            // indicates if the current player will be skipped

public:
    Game(GameMode *mode);                                       // Constructor
    void setSpecialCards(SpecialActionCard *specialActionCard); // stores the SpecialActionCard objects in the specialCards vector
    void start();                                               // Main game cycle
    bool isValidMove(Card *card);                               // checks if a move is valid
    bool isClockwise();                                         // returns the direction of the game
    bool checkForWinner();                                      // checks for winner every turn
    void reverseDirection();                                    // reverses the direction of the game
    void skipPlayer();                                          // increases player index by 1
    void forceDraw(int numCards);                               // make the next player draw numCards no. of cards
    void setWillSkip(bool willSkip);                            // setter for willSkip
    void changeColor(Color newColor);                           // setter for currentColor
    Player *getCurrentPlayer();                                 // returns current Player
    Player *getNextPlayer();                                    // returns next Player
    Player *getPreviousPlayer();                                // returns previous Player
    Player *getPlayer(int i);                                   // returns Player with index i
    int getCurrentPlayerIndex();                                // returns currentPlayerIndex
    int getTempPlayerIndex();                                   // returns tempPlayerIndex
    void setCurrentPlayerIndex(int index);                      // changes currentPlayerIndex
    void updateCurrentCard(Card *card);                         // updates the current card in play
    bool isGameOver();                                          // checks if game is over
    vector<SpecialActionCard *> *getSpecialCards();             // returns the vectors of the pointers to the SpecialActionCard objects
    void specialActionCheck();                                  // checks if there is a special action stored
    void specialDraw(int numCards, int playerIndex);            // make a player with index playerindex draw numCards no. of cards
    bool isFirstTurn();                                         // checks if it is first turn and sets it to false
    bool isGameError();                                         // checks if the Draw Pile is empty
    void play();                                                // handles the turn of each player
    string colorToString(Color color);                          // convert Color to string
    vector<Player *> getPlayers() const;                        // returns the vector of player objects
    string getWinnerName() const;                               // returns the name of the winner
    void loadScores();                                          // load the scoreboard from the txt file to playerScores
    void saveScores();                                          // saves the scores to the txt file
    void printScores();                                         // prints the first 10 entries of the scoreboard in descending order
    void updateScores(string winnerName);                       // updates the playerScores with the name and score of the new winner
    ~Game();                                                    // Destructor
};

#endif // GAME_H