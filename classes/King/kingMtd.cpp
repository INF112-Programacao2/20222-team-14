//
// Created by pedro on 14/10/2022.
//
#include <cstdlib>
#include "../Piece/Piece.h"
#include "King.h"

King::King(char name, int team) : Piece(name, team) {

}

King::~King() {
}

bool King::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if ((abs(xPosition - xDest) <= 1 && yDest == yPosition) || (abs(yPosition - yDest) <= 1 && xDest == yDest)) {
        return true;
    }
    return false;
}