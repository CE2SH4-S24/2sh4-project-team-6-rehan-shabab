#include "GameMechs.h"
#include "MacUILib.h"

using namespace std;

//constructors
GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;

    foodPos.setObjPos(-1, -1, 'o');
}

//constructors
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX > 0 ? boardX : 20;
    boardSizeY = boardY > 0 ? boardY : 10;
    foodPos.setObjPos(-1, -1, 'o'); 
}

// deconstructor
GameMechs::~GameMechs() {
    // Destructor implementation
    // Add code to release any allocated resources
}

// exit flag status
bool GameMechs::getExitFlagStatus(){
    return exitFlag;
}
void GameMechs::setExitTrue(){
    exitFlag = true;
}

//lose flag status
bool GameMechs::getLoseFlagStatus(){
    return loseFlag;
}
void GameMechs::setLoseFlag(){
    loseFlag = true;
}

// current score
int GameMechs::getScore(){
    return score;
}

void GameMechs::incrementScore()
{
    score += 1; //increment score by 1
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

//Generates a new food position
void GameMechs::generateFood(objPosArrayList *blockOff) {
    srand(time(NULL));

    foodPos.x = (rand() % (boardSizeX-2))+1;
    foodPos.y = (rand() % (boardSizeY-2))+1;

    objPos tempPos;

    //checks for overlap with blockOff positions
    for (int i = 0; i < blockOff->getSize(); i++){
        blockOff ->getElement(tempPos, i);
        while(foodPos.isPosEqual(&tempPos)){
            foodPos.x = (rand() % (boardSizeX-2))+1;
            foodPos.y = (rand() % (boardSizeY-2))+1;
        }
    }
}

// get current food position
void GameMechs::getFoodPos(objPos &returnFood) {
    returnFood.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}