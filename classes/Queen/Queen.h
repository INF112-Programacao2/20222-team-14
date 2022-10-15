//
// Created by pedro on 15/10/2022.
//

#ifndef INC_20222_TEAM_14_QUEEN_H
#define INC_20222_TEAM_14_QUEEN_H


class Queen : public Piece {
public:
    Queen(char name, int team);

    ~Queen();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //INC_20222_TEAM_14_QUEEN_H
