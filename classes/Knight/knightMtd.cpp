//
// Created by pedro on 14/10/2022.
//
#include "../Piece/Piece.h"
#include "Knight.h"

Knight::Knight(char name, int team) : Piece(name, team) {

}

Knight::~Knight() {
}

bool Knight::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    return false;
}