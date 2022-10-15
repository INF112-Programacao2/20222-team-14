//
// Created by pedro on 14/10/2022.
//

#ifndef INC_20222_TEAM_14_KING_H
#define INC_20222_TEAM_14_KING_H


class King : public Piece {
public:
    King(char name, int team);

    ~King();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //INC_20222_TEAM_14_KING_H
