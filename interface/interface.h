
#ifndef INC_20222_TEAM_14_INTERFACE_H
#define INC_20222_TEAM_14_INTERFACE_H


#include "../controllers/BoardController/BoardController.h"


#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <iostream>
using namespace sf;
//header file for the interface class
class Interface {
private:
    Sprite f[32];
    BoardController *boardController;
   
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
    
   
public:
    std::string move;
    bool draw = false;
    std::string position;
    void moveB(std::string str);
    bool caled = false;
     void loadPosition();
     void promotion();
     void moveBack();
    Interface(BoardController *boardController);
    void drawBoard();
    void movePiece( std::string move);
    void showStatus();
    void checkPromotion(char piece);
    bool verifyCheckMate();
    std::string handleMove(std::string move);
};

#endif //INC_20222_TEAM_14_INTERFACE_H





