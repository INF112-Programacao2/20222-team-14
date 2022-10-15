//
// Created by pedro on 13/10/2022.
//
#include "../Piece/Piece.h"
#include "Tower.h"

Tower::Tower(char name, int team) : Piece(name, team) {

}

Tower::~Tower() {
}

bool Tower::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (xPosition - xDest == yPosition - yDest == 0) {
        return true;
    }
    return false;
}