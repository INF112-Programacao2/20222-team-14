#include "../../classes/Board/Board.h"

class BoardController {
private:
    Board *board;
public:
    BoardController();

    ~BoardController();

    void startGame();

    void drawBoard();

    void movePiece();
};