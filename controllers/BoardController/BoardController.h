#include "../../classes/Board/Board.h"

class BoardController {
private:
    Board *board;
    bool inGame;
public:
    BoardController();

    ~BoardController();

    void startGame();
    void endGame();

    void drawBoard();

    void movePiece();

    void showStatus();
};