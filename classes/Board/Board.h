#ifndef INC_20222_TEAM_14_Board_H
#define INC_20222_TEAM_14_Board_H


#include "../Piece/TotalPiece.h"
#include "../Cell/Cell.h"
#include "../King/King.h"
#include "../Knight/Knight.h"
#include "../Rook/Rook.h"
#include "../Queen/Queen.h"
#include "../Bishop/Bishop.h"
#include "../Pawn/Pawn.h"
#include "../PieceIndex/PieceIndex.h"
#include <string>

using namespace std;

class Board {
private:
    Cell **cells;
    int playerTime;
    Board(Board const &board);

public:
    Board();

    ~Board();

    string movePiece(PieceIndex piecePosition, PieceIndex destinationPosition,bool isVirtual,bool justCheck);

    bool isGameOver();

    Cell *getCell(int x, int y);

    int getTurn();

    TotalPiece getTotalPieces();

    void promotePiece(Piece *piece, int xDestinationPosition, int yDestinationPosition);

    bool isKingInCheck(int team);

    bool isKingInCheckMate(int team);

    static PieceIndex * convertPosition(const string& piecePosition);
};

#endif //INC_20222_TEAM_14_Board_H