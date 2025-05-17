#ifndef GAME_H
#define GAME_H

#include"GameMode.h"
#include"Player.h"
#include"Deck.h"
#include"Card.h"

class Game{
    protected:
        vector<Player*> players;
        Deck* deck;
        GameMode* gameMode;
        Card* currentCard;
        int currentPlayerIndex;
        bool isClockwise;
        Color currentColor;
        bool gameOver;
        int drawStack;
    public:
        void initialize(int numPlayers, GameMode* mode);
        void start();
        void nextTurn();
        bool isValidMove(Card* card);
        void playCard(Card* card);
        void drawCard();
        bool checkForWinner();
        void handleSpecialCard(Card* card);
        void reverseDirection();
        void skipNextPlayer();
        void forceDraw(int numCards);
        void changeColor(Color newColor);
        Player* getCurrentPlayer();
        Player* getNextPlayer();
        void updateCurrentCard(Card* card);
        bool isGameOver();
        void endGame();
};

#endif //GAME_H