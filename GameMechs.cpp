#include "GameMechs.h" 
#include "MacUILib.h"  

using namespace std; 

// Default constructor for the GameMechs class
GameMechs::GameMechs()
{
    input = 0;  // Initialize input to 0 (no input)
    score = 0;  // Initialize score to 0
    exitFlag = false;  // Initialize exit flag to false
    loseFlag = false;  // Initialize lose flag to false
    boardSizeX = 20;  // Set default width of the game board to 20
    boardSizeY = 10;  // Set default height of the game board to 10

    // Initialize the food position to an invalid position (-1, -1) with symbol 'o'
    foodPos.setObjPos(-1, -1, 'o');
}

// Parameterized constructor for the GameMechs class
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;  // Initialize input to 0 (no input)
    score = 0;  // Initialize score to 0
    exitFlag = false;  // Initialize exit flag to false
    loseFlag = false;  // Initialize lose flag to false

    // Set the width of the game board to the provided value or default to 20 if the value is invalid
    boardSizeX = boardX > 0 ? boardX : 20;
    
    // Set the height of the game board to the provided value or default to 10 if the value is invalid
    boardSizeY = boardY > 0 ? boardY : 10;

    // Initialize the food position to an invalid position (-1, -1) with symbol 'o'
    foodPos.setObjPos(-1, -1, 'o');
}

// Destructor for the GameMechs class
GameMechs::~GameMechs() {
    // Destructor implementation
    // Add code to release any allocated resources (if any)
}

// Method to get the status of the exit flag
bool GameMechs::getExitFlagStatus(){
    return exitFlag;
}

// Method to set the exit flag to true
void GameMechs::setExitTrue(){
    exitFlag = true;
}

// Method to get the status of the lose flag
bool GameMechs::getLoseFlagStatus(){
    return loseFlag;
}

// Method to set the lose flag to true
void GameMechs::setLoseFlag(){
    loseFlag = true;
}

// Method to get the player's current score
int GameMechs::getScore(){
    return score;
}

// Method to increment the player's score by a specified number of points (default is 1)
void GameMechs::incrementScore(int points)
{
    score += points;  // Increment score by given points
}

// Method to get user input
char GameMechs::getInput()
{
    // Check if there is any input available
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();  // Get the input character
    }

    return input;  // Return the input character
}

// Method to get the width of the game board
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

// Method to get the height of the game board
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

// Method to set user input
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Method to clear the input buffer
void GameMechs::clearInput()
{
    input = '\0';  // Set input to null character
}

// Method to generate a new food position on the game board
void GameMechs::generateFood(objPosArrayList *blockOff) {
    srand(time(NULL));  // Seed the random number generator with the current time

    // Generate random x and y positions within the game board boundaries
    foodPos.x = (rand() % (boardSizeX - 2)) + 1;
    foodPos.y = (rand() % (boardSizeY - 2)) + 1;

    objPos tempPos;  // Temporary variable to store positions

    // Check for overlap with blocked positions
    for (int i = 0; i < blockOff->getSize(); i++) {
        blockOff->getElement(tempPos, i);  // Get the blocked position at index i
        // If the generated food position overlaps with a blocked position, generate a new position
        while (foodPos.isPosEqual(&tempPos)) {
            foodPos.x = (rand() % (boardSizeX - 2)) + 1;
            foodPos.y = (rand() % (boardSizeY - 2)) + 1;
        }
    }
}

// Method to get the current food position
void GameMechs::getFoodPos(objPos &returnFood) {
    // Set the return position to the current food position
    returnFood.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
