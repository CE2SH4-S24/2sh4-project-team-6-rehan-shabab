#ifndef OBJPOS_H 
#define OBJPOS_H

class objPos
{
    public:
        int x;  // x-coordinate of the position
        int y;  // y-coordinate of the position
        char symbol;  // ASCII symbol representing the position

        objPos();
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym);

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  
        void getObjPos(objPos &returnPos);
        char getSymbol();

        bool isPosEqual(const objPos* refPos);
        
        char getSymbolIfPosEqual(const objPos* refPos);
};

#endif
