#include "Piece.h"

Piece::Piece(char name, int team) {
    this->name = name;
    this->team = team;
}

Piece::~Piece(){
    delete this;
}

char Piece::getName() const {
    return name;
}


int Piece::getTeam() const {
    return team;
}


