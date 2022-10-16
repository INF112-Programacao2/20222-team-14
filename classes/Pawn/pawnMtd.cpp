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
    int wDestRange = xPosition + 1;
    int bDestRange = xPosition - 1;
    if (this->getQuantMoves() == 0) {
        wDestRange = xPosition + 2;
        bDestRange = xPosition - 2;
    }
    if (yPosition == yDest) {
        if (this->getTeam() == 1 && xDest >= wDestRange) {
            return true;
        } else if (this->getTeam() == 0 && xDest >= bDestRange) {
            return true;
        }
    }
    return false;
}

bool Pawn::canKill(Piece &piece, int xPosition, int yPosition, int xDest, int yDest) {
    if (piece.getTeam() != this->getTeam()) {
        if (this->getTeam() == 1 && xDest == xPosition + 1 && (yDest == yPosition + 1 || yDest == yPosition - 1)) {
            return true;
        } else if (this->getTeam() == 0 && xDest == xPosition - 1 &&
                   (yDest == yPosition + 1 || yDest == yPosition - 1)) {
            return true;
        }
    }
    return false;
}