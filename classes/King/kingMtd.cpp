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
    if ((abs(xPosition - xDest) <= 1 && yDest == yPosition) || (abs(yPosition - yDest) <= 1 && xDest == xPosition)) {
        return true;
    }
    if (abs(xPosition - xDest) == 1 && abs(yPosition - yDest) == 1) {
        return true;
    }
    return false;
}