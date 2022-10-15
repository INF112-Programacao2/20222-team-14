#ifndef INC_20222_TEAM_14_Board_H
#define INC_20222_TEAM_14_Board_H


#include "../Piece/TotalPiece.h"
#include "../Cell/Cell.h"
#include "../King/King.h"
#include "../Knight/Knight.h"
#include "../Tower/Tower.h"
#include "../Bishop/Bishop.h"
#include "../Pawn/Pawn.h"
#include <string>

using namespace std;

class Board {
private:
    Cell **cells;
    int playerTime;


public:
    Board();

    ~Board();

    void movePiece(string piecePosition, string destinationPosition);

    bool isGameOver();

    Cell *getCell(int x, int y);

    int getTurn();

    TotalPiece getTotalPieces();
};

#endif //INC_20222_TEAM_14_Board_H