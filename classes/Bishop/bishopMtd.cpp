//
// Created by pedro on 13/10/2022.
//
#include <cstdlib>
#include "../Piece/Piece.h"
#include "Bishop.h"

Bishop::Bishop(char name, int team) : Piece(name, team) {

}

Bishop::~Bishop() {
}

bool Bishop::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (abs(xPosition - xDest) == abs(yPosition - yDest)) {
        return true;
    }
    return false;
}