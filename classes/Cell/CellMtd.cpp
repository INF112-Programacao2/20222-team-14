#include "Cell.h"
Cell::Cell() {
    this->piece = nullptr;
    this->isOccupied = false;
}

Cell::~Cell() {
    delete piece;
}

void Cell::setPiece(Piece *newPiece) {
    this->piece = newPiece;
    this->isOccupied = true;
}

Piece *Cell::getPiece() {
    return this->piece;
}