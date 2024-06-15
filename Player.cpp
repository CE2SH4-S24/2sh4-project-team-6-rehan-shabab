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
    case 'W':
    case 'w':
        if (myDir != UP && myDir != DOWN)
            myDir = UP;
        break;
    case 'S':
    case 's':
        if (myDir != UP && myDir != DOWN)
            myDir = DOWN;
        break;
    case 'A':
    case 'a':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'D':
    case 'd':
        if (myDir != LEFT && myDir != RIGHT)
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
void Player::movePlayer()
{
    if (playerPosList->getSize() == 0) return; // Safety check

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

    // Set the correct symbol for the snake head
    currentHead.symbol = '@';

    // Update the player's position list, inserting the new head
    playerPosList->insertHead(currentHead);
}

// Checks for self-collision by comparing the head position with the rest of the body.
bool Player::collision()
{
    if (playerPosList->getSize() == 0) return false; // Safety check

    objPos head;
    playerPosList->getHeadElement(head);

    objPos tempBody;
    // Iterate through the player's body and check for collision with the head.
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
