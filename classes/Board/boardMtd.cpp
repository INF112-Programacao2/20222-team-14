#include "Board.h"

Board::Board() {
    this->pieces = new Piece *[8];
    for (int i = 0; i < 8; i++) {
        this->pieces[i] = new Piece[8];
        for (int j = 0; j < 8; j++) {
            this->pieces[i][j] = Piece(i, j);
        }

    }
}

Board::~Board() {
    delete this;
}