#ifndef INC_20222_TEAM_14_BoardController_H
#define INC_20222_TEAM_14_BoardController_H


#include "../../classes/Board/Board.h"

class BoardController {
private:
    Board *board;
    std::string position;
public:
    BoardController();

    ~BoardController();

    void startGame();
    void endGame();

    void drawBoard();

    void movePiece();

    void showStatus();

    void checkPromotion(char piece);

    bool verifyCheckMate();

    string handleMove(string move);
};

#endif //INC_20222_TEAM_14_BoardController_H