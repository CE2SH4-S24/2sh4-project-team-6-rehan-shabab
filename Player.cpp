#include "Player.h"
#include "GameMechs.h"

// Constructor: Initializes the Player object with a reference to the GameMechs instance and sets initial position.
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

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
    delete playerPosList;
}

// Getter for player position list.
objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

// Updates the player's direction based on user input.
void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    switch (input)
    {
    case 27:
        mainGameMechsRef->setExitTrue();
        break;
    case 'w':
        if (myDir != UP && myDir != DOWN)
            myDir = UP;
        break;
    case 's':
        if (myDir != UP && myDir != DOWN)
            myDir = DOWN;
        break;
    case 'a':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'd':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = RIGHT;
        break;
    case ' ': // If space is pressed, set direction to STOP
        myDir = STOP;
        break;
    default:
        // Handle other cases or do nothing for unrecognized input
        break;
    }
}

// Moves the player based on the current direction.
void Player::movePlayer()
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Update the head position based on the current direction.
    switch (myDir)
    {
    case UP:
        currentHead.y--;
        if (currentHead.y <= 0)
            currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
        break;
    case RIGHT:
        currentHead.x++;
        if (currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            currentHead.x = 1;
        break;
    case LEFT:
        currentHead.x--;
        if (currentHead.x <= 0)
            currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
        break;
    case DOWN:
        currentHead.y++;
        if (currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            currentHead.y = 1;
        break;
    default:
        break;
    }
    // Update the player's position list, inserting the new head and removing the tail.
    playerPosList->insertHead(currentHead);
    playerPosList->removeTail();
}

// Checks for self-collision by comparing the head position with the rest of the body.
bool Player::collision()
{
    objPos head;
    objPos tempBody;
    playerPosList->getHeadElement(head);

    // Iterate through the player's body and check for collision with the head.
    for (int i = 2; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(tempBody, i);
        if (tempBody.isPosEqual(&head))
        {
            return true;
        }
    }
    return false;
}