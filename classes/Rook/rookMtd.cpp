//
// Created by pedro on 13/10/2022.
//
#include "../Piece/Piece.h"
#include "Rook.h"

Rook::Rook(char name, int team) : Piece(name, team) {

}

Rook::~Rook() {
}

bool Rook::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (xPosition == xDest || yPosition == yDest) {
        return true;
    }
    return false;
}