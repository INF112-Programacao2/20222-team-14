#include "Piece.h"

Piece::Piece(char name, int team) {
    this->name = name;
    this->team = team;
    this->quantMoves = 0;
}

Piece::~Piece() {
    delete this;
}

char Piece::getName() const {
    return name;
}


int Piece::getTeam() const {
    return team;
}

int Piece::getQuantMoves() const {
    return quantMoves;
}

void Piece::setQuantMoves(int nQuantMoves) {
    this->quantMoves = nQuantMoves;
}

void Piece::incrementQuantMoves() {
    this->quantMoves++;
}

bool Piece::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    return true;
}

bool Piece::canKill(Piece &piece, int xPosition, int yPosition, int xDest, int yDest) {
    return true;
}

bool Piece::checkPromotion(int xPosition, int yPosition) {
    return false;
}
