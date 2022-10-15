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

void Cell::removePiece() {
    this->piece = nullptr;
    this->isOccupied = false;
}

Piece *Cell::getPiece() {
    return this->piece;
}