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
    bool playWithEngin{};
    explicit Board(Board *board);
    bool firstMove;

public:
    Board();

    ~Board();

    string movePiece(PieceIndex piecePosition, PieceIndex destinationPosition,bool isVirtual,bool justCheck);
    string castling(string clastlingType);
    bool isGameOver();

    Cell *getCell(int x, int y);

    int getTurn();

    TotalPiece getTotalPieces();

    PieceIndex checkPromotion();

    void promotePiece(Piece *piece, PieceIndex pieceIndex);

    bool isKingInCheck(int team);

    bool isKingInCheckMate();

    static PieceIndex * convertPosition(const string& piecePosition);

    bool getPlayWithEngin();
    void setPlayWithEngin(bool nPlayWithEngin);

    bool getFirstMove();
    void setFirstMove(bool nFirstMove);
};

#endif //INC_20222_TEAM_14_Board_H