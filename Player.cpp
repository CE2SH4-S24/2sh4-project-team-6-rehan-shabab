#include "Player.h"
#include "GameMechs.h"

// Constructor: Initializes the Player object with a reference to the GameMechs instance and sets initial position.
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;  // Store the reference to the GameMechs object
    myDir = STOP;  // Initialize the direction to STOP

    // Set initial position in the middle of the game board
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    // Initialize playerPosList with the initial position
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

// Destructor: Frees dynamically allocated memory.
Player::~Player()
{
    delete playerPosList;  // Delete the objPosArrayList to free the allocated memory
}

// Getter for player position list.
objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;  // Return the player's position list
}

// Updates the player's direction based on user input.
void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();  // Get the input from the GameMechs object

    switch (input)
    {
    case 27:  // ESC key
        mainGameMechsRef->setExitTrue();
        break;
    case 'w':
        if (myDir != UP && myDir != DOWN)  // Prevent reversing direction
            myDir = UP;
        break;
    case 's':
        if (myDir != UP && myDir != DOWN)  // Prevent reversing direction
            myDir = DOWN;
        break;
    case 'a':
        if (myDir != LEFT && myDir != RIGHT)  // Prevent reversing direction
            myDir = LEFT;
        break;
    case 'd':
        if (myDir != LEFT && myDir != RIGHT)  // Prevent reversing direction
            myDir = RIGHT;
        break;
    case ' ':
        myDir = STOP;
        break;
    default:
        break;
    }
}

// Moves the player based on the current direction.
// This method updates the head position of the snake and handles wraparound at the game board boundaries.
void Player::movePlayer()
{
    // Ensure the player has a body segment
    if (playerPosList->getSize() == 0) return;

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Update the head position based on the current direction
    switch (myDir)
    {
    case UP:
        currentHead.y--;
        // Handle wraparound at the top boundary
        if (currentHead.y <= 0)
            currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        break;
    case RIGHT:
        currentHead.x++;
        // Handle wraparound at the right boundary
        if (currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            currentHead.x = 1;
        break;
    case LEFT:
        currentHead.x--;
        // Handle wraparound at the left boundary
        if (currentHead.x <= 0)
            currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        break;
    case DOWN:
        currentHead.y++;
        // Handle wraparound at the bottom boundary
        if (currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            currentHead.y = 1;
        break;
    default:
        break;
    }

    // Set the correct symbol for the snake head
    currentHead.symbol = '@';

    // Update the player's position list, inserting the new head
    playerPosList->insertHead(currentHead);
    // Remove the tail to simulate movement
    playerPosList->removeTail();
}

// Checks for self-collision by comparing the head position with the rest of the body.
// Returns true if the head collides with any other part of the snake, otherwise false.
bool Player::collision()
{
    // Safety check: ensure the player has a body segment
    if (playerPosList->getSize() == 0) return false;

    objPos head;
    playerPosList->getHeadElement(head);

    objPos tempBody;
    // Iterate through the player's body segments and check for collision with the head
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(tempBody, i);
        if (tempBody.isPosEqual(&head))
        {
            return true;
        }
    }
    return false;
}
