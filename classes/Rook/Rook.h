#ifndef INC_20222_TEAM_14_Rook_H
#define INC_20222_TEAM_14_Rook_H

class Rook : public Piece {
public:
    Rook(char name, int team);

    ~Rook();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //INC_20222_TEAM_14_Rook_H