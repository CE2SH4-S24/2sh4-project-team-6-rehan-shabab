#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "objPosArrayList.h"
#include "objPos.h"

class Food {
private:
    objPos foodPos; // Declare foodPos here
    GameMechs* gameMechsRef;

public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void generateFood(objPosArrayList* playerPosList);
    void getFoodPos(objPos &returnPos);
};

#endif // FOOD_H
