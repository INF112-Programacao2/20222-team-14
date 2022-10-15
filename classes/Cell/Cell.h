#ifndef INC_20222_TEAM_14_Cell_H
#define INC_20222_TEAM_14_Cell_H

#include "../Piece/Piece.h"
class Cell {
private:
    Piece *piece;
public:
    bool isOccupied;

    Cell();

    ~Cell();

    void setPiece(Piece *piece);

    void removePiece();

    Piece *getPiece();
};

#endif //INC_20222_TEAM_14_Cell_H

