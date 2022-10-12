
#include "../Piece/Piece.h"

class Cell {
private:
    Piece *piece;
public:
    bool isOccupied;
    Cell();

    ~Cell();

    void setPiece(Piece *piece);
    Piece *getPiece();
};