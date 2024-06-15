#include "Food.h"
#include <cstdlib>  
#include <ctime>    

// Constructor for the Food class, initializing the food list and seeding the random number generator
Food::Food(GameMechs* thisGMRef) {
    gameMechsRef = thisGMRef;  // Store the reference to the GameMechs object
    foodList = new objPosArrayList();  // Create a new objPosArrayList to store food items
    srand(time(nullptr));  // Seed the random number generator with the current time
}

// Destructor for the Food class, cleaning up the dynamically allocated food list
Food::~Food() {
    delete foodList;  // Delete the objPosArrayList to free the allocated memory
}

// Method to generate multiple food items on the game board, avoiding collision with the player
void Food::generateFood(objPosArrayList* playerPosList) {
    // Clear all previous food items from the food list
    while (foodList->getSize() > 0) {
        foodList->removeTail();  // Remove the last element in the food list
    }

    // Generate 5 food items
    for (int i = 0; i < 5; ++i) {
        objPos newFood;  // Temporary variable to store the new food position
        bool playerOverlap;  // Flag to check if the new food position overlaps with the player

        // Find a new food position that does not overlap with the player
        do {
            // Generate a random position for the new food item within the game board boundaries
            newFood.x = (rand() % (gameMechsRef->getBoardSizeX() - 2)) + 1;
            newFood.y = (rand() % (gameMechsRef->getBoardSizeY() - 2)) + 1;

            playerOverlap = false;  // Reset the overlap flag
            objPos playerPos;  // Temporary variable to store player positions

            // Check the new food position against all player positions to ensure no overlap
            for (int j = 0; j < playerPosList->getSize(); ++j) {
                playerPosList->getElement(playerPos, j);  // Get the player position at index j
                if (newFood.isPosEqual(&playerPos)) {  // Check if the new food position is equal to the player position
                    playerOverlap = true;  // Set the overlap flag to true
                    break;  // Exit the loop early if an overlap is found
                }
            }
        } while (playerOverlap);  // Repeat until a non-overlapping position is found

        // Set the symbol for the new food item ('S' for special, 'o' for regular)
        newFood.symbol = (i == 0) ? 'S' : 'o';  // The first food item is special

        // Add the new food item to the food list
        foodList->insertTail(newFood);
    }
}

// Method to get the position of a food item by index
void Food::getFoodPos(objPos &returnPos, int index) {
    foodList->getElement(returnPos, index);  // Retrieve the food item at the specified index and store it in returnPos
}

// Method to get the count of food items currently in the food list
int Food::getFoodCount() {
    return foodList->getSize();  // Return the number of food items in the food list
}
