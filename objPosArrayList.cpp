#include "objPosArrayList.h"
#include <stdexcept> // for std::out_of_range

// Constructor
objPosArrayList::objPosArrayList() {
    aList = new objPos[ARRAY_MAX_CAP];
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;

    // Initialize all elements with default objPos
    for (int i = 0; i < sizeArray; i++) {
        aList[i] = objPos(); // Assuming objPos has a default constructor
    }
}

// Destructor
objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

// Get the size of the list
int objPosArrayList::getSize() {
    return sizeList;
}

// Insert an element at the head of the list
void objPosArrayList::insertHead(objPos thisPos) {
    if (sizeList == sizeArray) {
        return;
    }
    for (int i = sizeList; i > 0; i--) {
        aList[i].setObjPos(aList[i - 1]);
    }
    aList[0].setObjPos(thisPos);
    sizeList++;
}

// Insert an element at the tail of the list
void objPosArrayList::insertTail(objPos thisPos) {
    if (sizeList == sizeArray) {
        return;
    }
    aList[sizeList].setObjPos(thisPos);
    sizeList++;
}

// Remove the head element from the list
void objPosArrayList::removeHead() {
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; i++) {
            aList[i].setObjPos(aList[i + 1]);
        }
        sizeList--;
    }
}

// Remove the tail element from the list
void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--;
    }
}

// Get the head element of the list
void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos.setObjPos(aList[0]);
    } else {
        throw std::out_of_range("List is empty");
    }
}

// Get the tail element of the list
void objPosArrayList::getTailElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos.setObjPos(aList[sizeList - 1]);
    } else {
        throw std::out_of_range("List is empty");
    }
}

// Get an element at a specific index
void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos.setObjPos(aList[index]);
    } else {
        throw std::out_of_range("Index out of range");
    }
}