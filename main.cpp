#include <iostream>

#include "AIPlayer.h"
#include "Deck.h"
#include "Game.h"
#include "GameMode.h"
#include "HumanPlayer.h"
#include "NumberCard.h"
#include "SpecialActionCard.h"
using namespace std;

// Flags and data to track game status
bool gameStarted = false;
bool gameOver = false;
string winnerName = "";
Game *currentGame = nullptr;

void showRules()
{
    cout << "\n===== UNO RULES =====\n";
    cout << "1. Each player starts with 7 cards.\n";
    cout << "2. The objective is to be the first player to get rid of all cards.\n";
    cout << "3. On your turn, match the top card by number, color, or action.\n";
    cout << "   Wild and Wild Draw Four cards can be played at any time.\n";
    cout << "4. If you can't play, draw a card.\n";
    cout << "5. Action cards:\n";
    cout << "   - Skip: Next player loses a turn\n";
    cout << "   - Reverse: Reverses direction\n";
    cout << "   - Draw Two: Next player draws 2 cards and skips turn\n";
    cout << "   - Wild: You choose the next color\n";
    cout << "   - Wild Draw Four: Choose a color and next player draws 4 + skips\n";
    cout << "6. Special Action card (your custom rule):\n";
    cout << "   - Choose an action card and target a player of your choice\n";
    cout << "7. UNO rule: Type 0 BEFORE playing your last card to call UNO.\n\n";
}

void showPlayerInfo(const string &playerName)
{
    cout << "\n===== PLAYER INFO =====\n";
    cout << "Name: " << playerName << endl;
    cout << "Bots: 3 (Bot1, Bot2, Bot3)\n";

    if (gameStarted || gameOver)
    {
        cout << "\n--- Remaining Cards ---\n";
        for (Player *p : currentGame->getPlayers())
        {
            cout << p->getName() << ": " << p->getHandSize() << " cards";
            if (gameOver && p->getName() == winnerName)
            {
                cout << "    WINNER";
            }
            cout << endl;
        }
    }
    cout << endl;
}

void showScoreboard(const string &filename = "scores.txt")
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Could not open " << filename << endl;
        return;
    }

    cout << "========== SCOREBOARD ==========\n";

    string line;
    bool hasScores = false;  // Track if any valid score line was found

    while (getline(infile, line))
    {
        istringstream iss(line);
        string nameOrIndex;
        int score;

        if (iss >> nameOrIndex >> score)
        {
            hasScores = true;
            cout << "   " << nameOrIndex << ": " << score << " points\n";
        }
    }

    if (!hasScores)
    {
        cout << "   No scores recorded yet." << endl;
    }

    cout << "====================================\n";
    infile.close();
}

int main()
{
    GameMode *mode = new GameMode;

    string choiceString;
    int choice;
    bool fastMode = false;
    while (true)
    {
        cout << "\n======= UNO GAME MAIN MENU =======\n";
        cout << "1. Start Game\n";
        cout << "2. Select Mode\n";
        cout << "3. View Rules\n";
        cout << "4. View Scoreboard\n";
        cout << "5. Exit\n";
        cout << "==================================\n";

        while (true)
        {
            cout << "\nEnter your choice: ";
            cin >> choiceString;
            try
            {
                choice = stoi(choiceString);
                break;
            }
            catch (const std::exception &e)
            {
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
        }

        if (choice == 1)
        {
            if (mode == nullptr)
            {
                mode = new GameMode;
            }
            cout << "\nStarting the UNO game" << "...\n\n";
            currentGame = new Game(mode);
            gameStarted = true;
            currentGame->start();
            gameOver = true;
            if (!currentGame->isGameError())
            {
                winnerName = currentGame->getWinnerName();
            }
            delete currentGame;
        }
        else if (choice == 2)
        {
            int modeInput;
            string modeInputString;
            while (true)
            {
                cout << "\nSelect GameMode:\n";
                cout << "1. Single-Player (default)\n";
                cout << "2. Multi-Player\n";
                cout << "3. Simulation\n";
                cout << "4. Fast mode";
                cout << (mode->getIsFast() ? " (On)\n\n" : " (Off)\n\n");
                cout << "Enter your choice: ";
                cin >> modeInputString;
                cout << endl;
                try
                {
                    modeInput = stoi(modeInputString);
                    if (modeInput == 1)
                    {
                        delete mode;
                        mode = new GameMode;
                        mode->setIsFast(fastMode);
                        break;
                    }
                    else if (modeInput == 2)
                    {
                        delete mode;
                        mode = new GameMode("multiplayer");
                        mode->setIsFast(fastMode);
                        break;
                    }
                    else if (modeInput == 3)
                    {
                        delete mode;
                        mode = new GameMode("simulation");
                        mode->setIsFast(fastMode);
                        cout << "Simulation Mode selected.\n";
                        break;
                    }
                    else if (modeInput == 4)
                    {
                        mode->setIsFast(!mode->getIsFast());
                        fastMode = mode->getIsFast();
                        cout << (mode->getIsFast() ? "Fast-mode is On\n" : "Fast-mode is Off\n");
                    }
                    else
                    {
                        cout << "Invalid input. Please try again." << endl;
                    }
                }
                catch (const exception &e)
                {
                    std::cout << "Invalid input. Please enter a number." << std::endl;
                    continue;
                }
            }
        }
        else if (choice == 3)
        {
            showRules();
        }
        else if (choice == 4)
        {
            showScoreboard();
            // currentGame->loadScores();
            // currentGame->printScores();
        }
        else if (choice == 5)
        {
            cout << "Exiting UNO Game. Bye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    delete currentGame; // clean up game pointer
    return 0;
}