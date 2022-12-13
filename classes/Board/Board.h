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
    bool playWithEngin;
    bool playEnginexEngine;

    explicit Board(Board *board);

    bool firstMove;
    int turns;
    int pieceCount;
    int turnsWithoutCapture;

public:
    Board();

    ~Board();

    string movePiece(PieceIndex piecePosition, PieceIndex destinationPosition, bool isVirtual, bool justCheck);

    string castling(const string &clastlingType);

    bool isGameOver();

    Cell *getCell(int x, int y);

    int getCurrentPlayer();

    TotalPiece getTotalPieces();

    PieceIndex checkPromotion();

    void promotePiece(Piece *piece, PieceIndex pieceIndex);

    bool isKingInCheck(int team);

    bool isKingInCheckMate();

    static PieceIndex *convertPosition(const string &piecePosition);

    bool getPlayWithEngin();

    void setPlayWithEngin(bool nPlayWithEngin);

    bool getPlayEnginexEngine();

    void setPlayEnginexEngine(bool nPlayEnginexEngine);

    int getPlayerTime();

    void setPlayerTime(int nPlayerTime);

    void togglePlayerTime();

    bool getFirstMove();

    void setFirstMove(bool nFirstMove);

    int getTurns();

    void setTurns(int nTurns);

    void incrementTurns();

    bool isKing(PieceIndex &pieceIndex);

    //criar empate por afogamento
    bool isStaleMate();

    //criar empate por posicao morta
    bool isDeadPosition();

    //criar empate por 50 jogadas
    bool isFiftyMoves();

    //criar empate por material insuficiente
    bool isInsufficientMaterial();

    char isDraw();

    int getTurnsWithoutCapture();
};


#endif //INC_20222_TEAM_14_Board_H