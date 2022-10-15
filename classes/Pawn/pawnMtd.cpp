//
// Created by pedro on 14/10/2022.
//
#include "../Piece/Piece.h"
#include "Pawn.h"

Pawn::Pawn(char name, int team) : Piece(name, team) {

}

Pawn::~Pawn() {
}

bool Pawn::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (yPosition == yDest) {
        if (this->getTeam() == 1 && xDest == xPosition + 1) {
            return true;
        } else if (this->getTeam() == 0 && xDest == xPosition - 1) {
            return true;
        }
    }
    return false;
}

bool Pawn::canKill(Piece &piece, int xPosition, int yPosition, int xDest, int yDest) {
    if (piece.getTeam() != this->getTeam()) {
        if (this->getTeam() == 1 && xDest == xPosition + 1 && (yDest == yPosition + 1 || yDest == yPosition - 1)) {
            return true;
        } else if (this->getTeam() == 0 && xDest == xPosition - 1 && (yDest == yPosition + 1 || yDest == yPosition - 1)) {
            return true;
        }
    }
    return false;
}