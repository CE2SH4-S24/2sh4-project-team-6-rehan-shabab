#ifndef PLAYER_H  
#define PLAYER_H

#include "GameMechs.h"  
#include "objPos.h" 
#include "objPosArrayList.h"  

class GameMechs;  // Forward declaration of the GameMechs class

// Player class definition
class Player
{
    // Public members and methods
    public:
        // Enum to represent the direction of the player's movement
        enum Dir {STOP, UP, DOWN, LEFT, RIGHT};  // This is the direction state (Finite State Machine)

        // Constructor: Initializes the Player object with a reference to the GameMechs instance
        Player(GameMechs* thisGMRef);

        // Destructor: Frees dynamically allocated memory
        ~Player(); 
        
        // Method to get the player's position list
        objPosArrayList* getPlayerPos();

        // Method to update the player's direction based on user input
        void updatePlayerDir();

        // Method to move the player based on the current direction
        void movePlayer();

        // Method to get the length of the snake
        int getSnakeLength() const;

        // Method to check for self-collision
        bool collision();
        
    // Private members and methods
    private:
        objPosArrayList* playerPosList;  // List to store the positions of the player's body segments
        enum Dir myDir;  // Current direction of the player's movement
        bool exitFlag;  // Flag to indicate if the player has chosen to exit the game
        GameMechs* mainGameMechsRef;  // Reference to the GameMechs object
};

#endif  // End of include guard
