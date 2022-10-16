#ifndef INC_20222_TEAM_14_BoardController_H
#define INC_20222_TEAM_14_BoardController_H


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

    void checkPromotion();
};

#endif //INC_20222_TEAM_14_BoardController_H