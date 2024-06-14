#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* player;
Food* food;

objPos myPos;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while(!myGM->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
    return 0;
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(26, 13);
    player = new Player(myGM);
    food = new Food(myGM);

    // Generate initial food
    objPosArrayList tempPosList;
    food->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    objPos tempFoodPos;
    objPos tempBody;
    objPosArrayList* playerBody = player->getPlayerPos();
    food->getFoodPos(tempFoodPos);

    player->updatePlayerDir();
    player->movePlayer();

    playerBody->getHeadElement(tempBody);
    if (tempBody.isPosEqual(&tempFoodPos))
    {
        myGM->incrementScore();
        playerBody->insertHead(tempFoodPos);  // Insert the food position as the new head
        food->generateFood(playerBody);
    }

    if (player->collision())
    {
        myGM->setLoseFlag();
    }

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;
    objPos tempBody;
    objPos tempFoodPos;

    objPosArrayList* playerBody = player->getPlayerPos();

    food->getFoodPos(tempFoodPos);
    MacUILib_printf(" S2024 Snake Game Project\n");

    for (int y = 0; y < myGM->getBoardSizeY(); ++y)
    {
        for (int x = 0; x < myGM->getBoardSizeX(); ++x)
        {
            drawn = false;
            for (int z = 0; z < playerBody->getSize(); z++)
            {
                playerBody->getElement(tempBody, z);
                if (x == tempBody.x && y == tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if (drawn) continue; // If player body is drawn, don't draw anything below

            if (y == 0 || y == myGM->getBoardSizeY() - 1 || x == 0 || x == myGM->getBoardSizeX() - 1)
            {
                // Draw borders
                MacUILib_printf("%c", '#');
            }

            else if (x == tempFoodPos.x && y == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
            else
                MacUILib_printf("%c", ' ');
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Press WASD to start or press ESC to exit\n");
    MacUILib_printf("Score: %d\n", myGM->getScore());

    if (myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nEnd Game.");
    }

    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nYou Lost.");
        myGM->setExitTrue();
    }

    MacUILib_printf("Food Pos: <%d, %d>\n", tempFoodPos.x, tempFoodPos.y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (myGM->getLoseFlagStatus()) {
        MacUILib_printf("\nYou Lost. Game Over.\n");
    } else {
        MacUILib_printf("\nEnd Game.\n");
    }
    MacUILib_uninit();
    delete myGM;
    delete player;
    delete food;
    exit(0);
}