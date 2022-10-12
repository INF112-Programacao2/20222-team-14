#include "../Piece/Piece.h"

class Board
{
private:
    Piece **pieces;
    bool inGame;

public:
    Board();
    ~Board();
};
