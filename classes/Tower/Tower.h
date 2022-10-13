#ifndef INC_20222_TEAM_14_Tower_H
#define INC_20222_TEAM_14_Tower_H

#include "../Piece/Piece.h"

class Tower : public Piece {
public:
    Tower(char name, int team);

    ~Tower();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //INC_20222_TEAM_14_Tower_H