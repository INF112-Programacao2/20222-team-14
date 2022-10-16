//
// Created by pedro on 14/10/2022.
//

#ifndef INC_20222_TEAM_14_PAWN_H
#define INC_20222_TEAM_14_PAWN_H


class Pawn : public Piece {
public:
    Pawn(char name, int team);

    ~Pawn();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;

    bool canKill(Piece &piece, int xPosition, int yPosition, int xDest, int yDest) override;

    bool checkPromotion(int xPosition, int yPosition) override;
};

#endif //INC_20222_TEAM_14_Pawn_H