#include <iostream>
#include "Food.h"
#include <cstdlib>
#include <ctime>

// Constructor for the Food class
Food::Food(GameMechs* thisGMRef)
{
    srand(time(nullptr));
    
    // Initialize food position to the center of the board
    int initialX = thisGMRef->getBoardSizeX() / 2;
    int initialY = thisGMRef->getBoardSizeY() / 2;
    foodPos.setObjPos(initialX, initialY, 'o');
}

// Destructor for the Food class
Food::~Food()
{
    // Destructor implementation (empty in this case)
}

// Function to generate a new food position, avoiding player overlap
void Food::generateFood(objPosArrayList* playerPosList)
{
    srand(time(nullptr));
    
    bool playerOverlap;

    // Loop until a valid food position is found
    do {
        foodPos.x = (rand() % 20) + 1;
        foodPos.y = (rand() % 10) + 1;

        playerOverlap = false;
        objPos playerPos;

        // Check for overlap with each player position
        for (int i = 0; i < playerPosList->getSize(); ++i) {
            playerPosList->getElement(playerPos, i);

            if (foodPos.isPosEqual(&playerPos)) {
                playerOverlap = true;
                break;
            }
        }
    } while (playerOverlap);

    // Set the symbol for the food position
    foodPos.symbol = 'o';
}

// Function to get the current food position
void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}