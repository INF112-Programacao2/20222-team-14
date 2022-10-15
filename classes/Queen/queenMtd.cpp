//
// Created by pedro on 15/10/2022.
//
#include <cstdlib>
#include "../Piece/Piece.h"

#include "Queen.h"

Queen::Queen(char name, int team) : Piece(name, team) {

}

Queen::~Queen() {
}

bool Queen::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (abs(xPosition - xDest) == abs(yPosition - yDest)) {
        return true;
    }
    if (xPosition == xDest || yPosition == yDest) {
        return true;
    }
    return false;
}