#include <iostream>  
#include "MacUILib.h"  
#include "objPos.h"  
#include "objPosArrayList.h"  
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std; 

#define DELAY_CONST 100000  // Define a constant for the delay duration (in microseconds)

GameMechs* myGM;  // Pointer to the GameMechs object
Player* player;  // Pointer to the Player object
Food* food;  // Pointer to the Food object

void Initialize(void);  // Function prototype for initialization
void GetInput(void);  // Function prototype for getting input
void RunLogic(void);  // Function prototype for running game logic
void DrawScreen(void);  // Function prototype for drawing the screen
void LoopDelay(void);  // Function prototype for adding a delay
void CleanUp(void);  // Function prototype for cleaning up

int main(void)
{
    Initialize();  // Call the initialization function

    // Main game loop, runs until the exit flag is set
    while (!myGM->getExitFlagStatus())
    {
        GetInput();  // Get user input
        RunLogic();  // Update game logic
        DrawScreen();  // Draw the updated screen
        LoopDelay();  // Add a delay to control the game speed
    }

    CleanUp();  // Call the cleanup function
    return 0;  // Return 0 to indicate successful execution
}

void Initialize(void)
{
    MacUILib_init();  // Initialize the Mac UI library
    MacUILib_clearScreen();  // Clear the screen

    // Create new instances of the game mechanics, player, and food objects
    myGM = new GameMechs(26, 13);
    player = new Player(myGM);
    food = new Food(myGM);

    // Generate initial food items on the game board
    food->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
    myGM->getInput();  // Get input from the user
}

void RunLogic(void)
{
    objPos tempFoodPos;  // Temporary variable for food position
    objPos tempBody;  // Temporary variable for player body position
    objPosArrayList* playerBody = player->getPlayerPos();  // Get the player's position list

    player->updatePlayerDir();  // Update the player's direction based on input
    player->movePlayer();  // Move the player in the current direction

    bool foodConsumed = false;  // Flag to check if food was consumed

    if (playerBody->getSize() > 0)  // Ensure the player has a body
    {
        playerBody->getHeadElement(tempBody);  // Get the player's head position

        // Check if the player's head position matches any food position
        for (int i = 0; i < food->getFoodCount(); ++i) {
            food->getFoodPos(tempFoodPos, i);  // Get the position of food at index i
            if (tempBody.isPosEqual(&tempFoodPos)) {  // Check if the head position equals the food position
                foodConsumed = true;  // Set the food consumed flag to true
                if (tempFoodPos.symbol == 'S') {  // Check if the food is special
                    // Special food effect: shorten snake by up to 10 segments and increment score by 10
                    int segmentsToRemove = std::min(10, playerBody->getSize() - 1);
                    for (int j = 0; j < segmentsToRemove; ++j) {
                        playerBody->removeTail();  // Remove segments from the tail
                    }
                    myGM->incrementScore(10);  // Increment score by 10 for special food
                } else {
                    myGM->incrementScore();  // Increment score by 1 for regular food
                }
                food->generateFood(playerBody);  // Generate new food items
                break;  // Exit the loop as food has been consumed
            }
        }

        if (!foodConsumed) {  // If no food was consumed
            playerBody->removeTail();  // Remove the tail to simulate movement
        }
    }

    if (player->collision()) {  // Check if the player collides with itself
        myGM->setLoseFlag();  // Set the lose flag
        myGM->setExitTrue();  // Set the exit flag
    }

    myGM->clearInput();  // Clear the input buffer
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  // Clear the screen

    bool drawn;  // Flag to check if an object was drawn
    objPos tempBody;  // Temporary variable for player body position
    objPos tempFoodPos;  // Temporary variable for food position

    objPosArrayList* playerBody = player->getPlayerPos();  // Get the player's position list

    MacUILib_printf(" S2024 Snake Game Project\n");  // Print the game title

    // Loop through each position on the game board
    for (int y = 0; y < myGM->getBoardSizeY(); ++y)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); ++x)
        {
            drawn = false;  // Reset the drawn flag
            for (int z = 0; z < playerBody->getSize(); z++)
            {
                playerBody->getElement(tempBody, z);  // Get the player body segment at index z
                if (x == tempBody.x && y == tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);  // Draw the player body segment
                    drawn = true;  // Set the drawn flag to true
                    break;  // Exit the loop as the object has been drawn
                }
            }

            if (drawn) continue;  // Continue to the next position if an object was drawn

            if (y == 0 || y == myGM->getBoardSizeY() - 1 || x == 0 || x == myGM->getBoardSizeX() - 1)
            {
                MacUILib_printf("%c", '#');  // Draw the border of the game board
            }
            else
            {
                // Check if the current position matches any food position
                for (int i = 0; i < food->getFoodCount(); ++i) {
                    food->getFoodPos(tempFoodPos, i);
                    if (x == tempFoodPos.x && y == tempFoodPos.y)
                    {
                        MacUILib_printf("%c", tempFoodPos.symbol);  // Draw the food item
                        drawn = true;  // Set the drawn flag to true
                        break;  // Exit the loop as the object has been drawn
                    }
                }

                if (!drawn) {
                    MacUILib_printf("%c", ' ');  // Draw an empty space
                }
            }
        }
        MacUILib_printf("\n");  // Move to the next line
    }

    // Print the game instructions and score
    MacUILib_printf("Press WASD to start or press ESC to exit\n");
    MacUILib_printf("Score: %d\n", myGM->getScore());

    if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nEnd Game.");  // Print the end game message if exit flag is set
    }

    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nYou Lost.");  // Print the lose message if lose flag is set
        myGM->setExitTrue();  // Set the exit flag
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);  // Add a delay to control the game speed
}

void CleanUp(void)
{
    MacUILib_clearScreen();  // Clear the screen
    if (myGM->getLoseFlagStatus()) {
        MacUILib_printf("\nYou Lost. Game Over.\n");  // Print the lose message if lose flag is set
    } else {
        MacUILib_printf("\nEnd Game.\n");  // Print the end game message if exit flag is set
    }
    MacUILib_uninit();  // Uninitialize the Mac UI library
    delete myGM;  // Delete the GameMechs object
    delete player;  // Delete the Player object
    delete food;  // Delete the Food object
    exit(0);  // Exit the program
}
