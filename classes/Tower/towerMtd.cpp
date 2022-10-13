//
// Created by pedro on 13/10/2022.
//

#include "Tower.h"

Tower::Tower(char name, int team) : Piece(name, team) {

}

Tower::~Tower(){
}

bool Tower::checkMove(int xPosition, int yPosition, int xDest, int yDest) {
    if (xPosition == xDest || yPosition == yDest) {
        return true;
    }
    return false;
}