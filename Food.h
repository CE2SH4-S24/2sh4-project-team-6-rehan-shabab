#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {
private:
    objPosArrayList* foodBucket;  // Food Bucket list member on the heap
    GameMechs* gameMechsRef;  // Reference to the GameMechs object

public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void generateFood(objPosArrayList* playerPosList);
    void getFoodPos(objPos &returnPos, int index);
    int getFoodCount();
};

#endif // FOOD_H
