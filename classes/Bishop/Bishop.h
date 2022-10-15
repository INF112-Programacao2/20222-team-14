#ifndef INC_20222_TEAM_14_Bishop_H
#define INC_20222_TEAM_14_Bishop_H


class Bishop : public Piece {
public:
    Bishop(char name, int team);

    ~Bishop();


    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //INC_20222_TEAM_14_Bishop_H