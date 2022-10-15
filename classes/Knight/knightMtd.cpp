//
// Created by pedro on 14/10/2022.
//
#include <cstdlib>
#include "../Piece/Piece.h"
#include "Knight.h"

Knight::Knight(char name, int team) : Piece(name, team) {

}

Knight::~Knight() {
}

bool Knight::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    int x = abs(xPosition - xDest);
    int y = abs(yPosition - yDest);
    if ((x == 1 && y == 2) || (x == 2 && y == 1)) {
        return true;
    } else {
        return false;
    }
}