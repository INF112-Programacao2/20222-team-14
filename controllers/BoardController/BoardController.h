#ifndef INC_20222_TEAM_14_BoardController_H
#define INC_20222_TEAM_14_BoardController_H


#include "../../classes/Board/Board.h"


class BoardController {
private:
    
    std::string position;
    std::string move;

public:
    Board *board;
    bool confirm;
    void setPosition(string s);
    BoardController();

    ~BoardController();

    void startGame();
    void endGame();
    void PubliccheckPromotion(char piece);
    void drawBoard();
    string pieceName;
    std::string res;
    string rawMove;
    void movePiece();
    std :: string getMove();

    void setMove(std::string move);

    void showStatus();

    void checkPromotion(char piece);

    bool verifyCheckMate();

    string handleMove(string move);
};

#endif //INC_20222_TEAM_14_BoardController_H