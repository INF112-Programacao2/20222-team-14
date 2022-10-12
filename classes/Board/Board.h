#include "../Cell/Cell.h"
#include "../Piece/TotalPiece.h"
#include <string>
using namespace std;
class Board
{
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
