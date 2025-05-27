Project Change Log Change 1: SpecialActionCard Functionality Enhancement Feature -SpecialActionCard target selection mechanism

Original Plan -SpecialActionCard would randomly select one of the action cards to apply its effect -No user interaction required for target selection

Actual Implementation -SpecialActionCard now allows the user to choose which player to target -Interactive target selection system implemented -User has control over who receives the action effect

Justification Advantages: -Enhanced Strategic Gameplay: Players can now make smart decisions about which opponent to target, adding depth to the game strategy -Improved Player Control: Gives players more control over their actions rather than relying on random chance -Better Game Balance: Prevents situations where random targeting might unfairly benefit or penalize players -Increased Engagement: Interactive decision-making keeps players more engaged in the gameplay

Reasoning: -The change from random selection to user choice transforms a luck-based mechanic into a skill-based one, which generally leads to more satisfying gameplay experiences and allows for more strategic thinking.

Change 2: HumanPlayer Interface and Turn Management Feature -Human player interaction system and turn menu

Original Plan -Automatic validation of cards in player's hand -Limited player interaction options -System automatically determines valid moves

Actual Implementation -Manual card validation by the player -Comprehensive turn menu system with multiple options: Play a card Draw a card View game rules Check remaining cards count for each player Exit the game -Error handling for invalid moves with appropriate messaging -Automatic guidance when no valid moves are available

Justification Advantages: -Improved User Experience: Clear menu options make the game more intuitive and user-friendly -Educational Value: Rules viewing option helps players learn and understand the game better -Improved Game Insight: Card count feature provides strategic information about game state -Better Error Handling: Clear feedback messages guide players when they make invalid moves -Increased Accessibility: Players can make decisions at their own pace rather than having the system decide for them

Reasoning: -This change transforms the interface from a passive system to an interactive one, giving players full control over their actions while providing helpful information and guidance. The comprehensive error handling ensures a smooth gameplay experience.

Change 3: Class Structure Enhancement Feature -Additional data members and methods for game classes to support better UNO game functionality

Original Plan Limited class functionality

Actual Implementation -Game Class Major Enhancements: Added Player* winner = nullptr to track who won Added bool firstTurn to handle special first turn rules Added map<string, int> playerScores to store player scores across multiple games Added bool gameError to track if any errors happen during the game Added void play() as main game loop Added void setSpecialCards(SpecialActionCard *specialActionCard) to manage special cards Added bool isClockwise() to track game direction Added Player *getPreviousPlayer() to get the last player Added Player *getPlayer(int i) to access any player by number Added int getCurrentPlayerIndex() to know whose turn it is Added vector<SpecialActionCard *> *getSpecialCards() to access special cards Added void specialActionCheck(Card prevTopCard) to handle action card effects Added void specialDraw(int numCards) for draw penalty cards Added bool isFirstTurn() to check if it's the first turn Added void firstActionPlay(ActionCard card) to handle first turn action cards Added string colorToString(Color color) to convert colors to text Added vector<Player *> getPlayers() const to access all players Added string getWinnerName() const to get winner's name Added void loadScores() to load saved scores from previous games Added void saveScores() to save current scores to file Added void printScores() to display all player scores Added void updateScores(std::string winnerName) to update winner's score

-GameMode Class Enhancements: Added int numOfPlayers to track how many players in the game Added bool isFast to control if the game runs in fast mode Added string getModeName() to get the game mode name Added int getWinningScore() to know what score wins the game Added int getNumOfPlayers() to get number of players Added bool getIsFast() to check if fast mode is on Added void setIsFast(bool turn) to turn fast mode on or off

-Card Class Enhancements: Added virtual string get_CardTypeString() = 0 to identify card types (Number, Action, Special) Added virtual ActionType get_ActionType() = 0 to get what action the card does Added virtual string get_ActionTypeString() = 0 to get action names as text Added virtual void specialAction(Game *game) for cards that do special things Added virtual int get_TargetPlayerIndex() to know which player gets affected

-NumberCard and ActionCard Classes: Added ActionType get_ActionType() override to tell what action they do Added string get_ActionTypeString() override to show action names Added string get_CardTypeString() override to identify themselves as Number or Action cards

-SpecialActionCard Class: Added string get_CardTypeString() override to identify as Special Action card Added int get_TargetPlayerIndex() override to track which player is targeted Added void specialAction(Game *game) override to perform the special action

-Player Class Enhancements: Added int playerIndex to track each player's position in the game Added bool isItHuman to know if player is human or AI Added bool getUno() to check if player has UNO (one card left) Added string getName() to get player's name Added bool isHuman() to check if player is human Added void displayHand() to show player's cards Added void setIndex(int index) to set player's position Added int getIndex() to get player's position Added string toLower(const string &str) to help with text processing Added Color chooseOptimalColor() for AI players to pick best color Added int calculateScore() to calculate player's score based on cards in hand

-HumanPlayer Class Changes: Removed void displayHand()( moved to base class), Card selectCard(), and Color selectColor() (changed approach) Added Game gameRef = nullptr to connect player to the game Added void setGame(Game* g) to set the game connection Added bool hasValidMove(Game* game) const to check if player can make a move

-Deck Class Enhancements: Added vector<Card *> get_cards() to access all cards in deck Added vector<Card *> get_discardPile() to access discard pile Added int get_DeckSize() const to check how many cards left in deck Added int get_DiscardSize() const to check discard pile size

Justification Advantages: -Complete UNO Features: All the new methods let us implement real UNO rules properly -Better Player Management: Player index and human/AI tracking makes game flow work correctly -Proper Card Handling: Card type identification helps the game know what each card does -Game State Tracking: Winner tracking, turn management, and direction control make the game work like real UNO -Flexible Game Modes: GameMode enhancements allow different ways to play UNO -Persistent scoring system that saves and loads player statistics -Fast mode functionality for quicker gameplay -Better Error Handling: Methods like hasValidMove() help prevent invalid moves -Cleaner Code Organization: Each class now has clear responsibilities

Reasoning: -Our original simple classes couldn't handle all the complex rules of UNO. Real UNO has many special situations like choosing colors, targeting players, tracking turn direction, handling first turn rules, and managing different game modes. These enhancements give us all the tools we need to create a complete and accurate UNO game that follows the real rules players expect.

Change 4: GameMode Enhancement Feature -The different ways players can play the UNO game

Original Plan -Three simple game modes: -No stacking for action cards -With stacking (players can stack action cards on top of each other) -Scoring system mode

Actual Implementation -Four main game modes: -Single-Player (default) - One human player against computer players -Multi-Player - Multiple human players can play together -Simulation - No human players, only AI players playing against each other -Fast Mode (Off/On) - When turned on, AI players make moves very quickly -When Fast Mode is turned on, players can still choose from the other three modes but AI moves happen much faster -Removed all stacking options - No modes allow card stacking anymore

Justification Advantages: -Better Player Experience: Single-Player mode is perfect for people who want to practice alone -More Social Options: Multiplayer mode lets friends play together on the same computer -Educational Value: Simulation mode lets people watch AI strategies and learn from them -Speed Control: Fast Mode lets people who want quick games get through them faster -Simpler Rules: Removing stacking makes the game easier to understand and less confusing -Clear Mode Selection: Four distinct modes are easier to understand

Reasoning: -The original stacking system was confusing and made games too complicated. Our new system focuses on different types of players and how they want to play. Some people want to play alone, some with friends, some just want to watch, and some want fast games. This gives everyone what they want while keeping the rules simple and clear.

Change 5: GUI Removal Feature -Graphical User Interface

Original Plan -Implementation of a graphical user interface for the game -Visual representation of game elements -GUI-based user interactions

Actual Implementation -Console-based interface only. -No GUI components implemented.

    Focus shifted to game logic and user experience in the terminal.

Justification Advantages: -Simplified Development: Removing GUI complexity allows more focus on core game logic. -Faster Implementation: Console interface is quicker to develop and debug. -Better Testing: Text-based interface is easier to test systematically. -Resource Efficiency: No need for graphics libraries or complex UI frameworks. -Academic Focus: The change supports the learning objectives focusing on game logic and coding skills instead of building a visual interface.

Reasoning: -Following tutor guidance, the decision to remove GUI was made to prioritize core functionality over visual presentation. This allows for more thorough development of game logic and ensures a more reliable foundation.

Change 6: Project Timeline and Focus Adjustment Feature -Development priorities and timeline

Original Plan -Balanced development between GUI and game logic -Timeline included significant GUI development phases -Equal emphasis on visual and functional aspects

Actual Implementation -Primary focus on game logic implementation

    Prioritized timeline for core functionality -GUI development time reallocated to logic refinement ~ Justification Advantages: -Improved Core Quality: More time devoted to game logic results in better functionality -Risk Reduction: Focusing on essential features reduces project risk -Educational Value: Deeper focus on algorithms and logic provides better learning outcomes -Deliverable Reliability: Prioritizing core features ensures a working product -Resource Optimization: Better allocation of development time to critical components

Reasoning: -The timeline adjustment reflects a strategic decision to ensure project success by focusing on the most critical aspects. This approach guarantees a functional game while allowing for potential future GUI enhancement.
