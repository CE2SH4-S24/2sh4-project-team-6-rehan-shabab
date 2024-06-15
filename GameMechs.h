#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>  
#include <time.h>  
#include "objPos.h"  
#include "objPosArrayList.h" 

using namespace std;  

// GameMechs class definition
class GameMechs
{
private:
    char input;  // Variable to store user input
    bool exitFlag;  // Flag to indicate if the game should exit
    bool loseFlag;  // Flag to indicate if the player has lost the game
    int score;  // Variable to store the player's score
    int boardSizeX;  // Width of the game board
    int boardSizeY;  // Height of the game board
    objPos foodPos;  // Position of the food on the game board

public:
    // Default constructor: Initializes the game mechanics with default board size
    GameMechs();

    // Parameterized constructor: Initializes the game mechanics with specified board size
    GameMechs(int boardX, int boardY);

    // Destructor: Cleans up any allocated resources
    ~GameMechs();

    // Method to get the status of the exit flag
    bool getExitFlagStatus();

    // Method to get the status of the lose flag
    bool getLoseFlagStatus();

    // Method to get user input
    char getInput();

    // Method to get the width of the game board
    int getBoardSizeX();

    // Method to get the height of the game board
    int getBoardSizeY();

    // Method to get the player's current score
    int getScore();

    // Method to set the exit flag to true
    void setExitTrue();

    // Method to set the lose flag to true
    void setLoseFlag();

    // Method to set user input
    void setInput(char this_input);

    // Method to clear the input buffer
    void clearInput();

    // Method to increment the player's score by a specified number of points (default is 1)
    void incrementScore(int points = 1);

    // Method to generate a new food position on the game board, avoiding specified blocked positions
    void generateFood(objPosArrayList *blockOff);

    // Method to get the current position of the food
    void getFoodPos(objPos &returnFood);
};

#endif  // End of include guard
