#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {
private:
    objPosArrayList* foodList;  // List to store multiple food items
    GameMechs* gameMechsRef;  // Reference to the GameMechs object

public:
    Food(GameMechs* thisGMRef);
    ~Food();

    void generateFood(objPosArrayList* playerPosList);
    void getFoodPos(objPos &returnPos, int index);
    int getFoodCount();
};

#endif // FOOD_H
