//
// Created by pedro on 18/10/2022.
//

#include "PieceIndex.h"

PieceIndex::PieceIndex() {
    this->xPosition = 0;
    this->yPosition = 0;
}

PieceIndex::PieceIndex(int xPosition, int yPosition) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
}

int PieceIndex::getXPosition() const {
    return xPosition;
}

int PieceIndex::getYPosition() const {
    return yPosition;
}

void PieceIndex::setXPosition(int xPosition) {
    this->xPosition = xPosition;
}

void PieceIndex::setYPosition(int yPosition) {
    this->yPosition = yPosition;
}