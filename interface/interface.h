
#ifndef INC_20222_TEAM_14_INTERFACE_H
#define INC_20222_TEAM_14_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include "../controllers/BoardController/BoardController.h"
#include <iostream>
using namespace sf;
//header file for the interface class
class Interface {
private:
    Sprite f[32];
    std::string position ;
    int board[8][8] =
            {-1, -2, -3, -4, -5, -3, -2, -1,
             -6, -6, -6, -6, -6, -6, -6, -6,
             0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,  0,  0,  0,
             6,  6,  6,  6,  6,  6,  6,  6,
             1,  2,  3,  4,  5,  3,  2,  1};
    std::string toChessNote(Vector2f p);
    Vector2f toCoord(char a, char b);
    void move(std::string str);
    void loadPosition();
public:
    Interface();
    void startGame();
    void endGame();
    void drawBoard();
    void movePiece(string move);
    void showStatus();
    void checkPromotion(char piece);
    bool verifyCheckMate();
    string handleMove(string move);
};

#endif //INC_20222_TEAM_14_INTERFACE_H





