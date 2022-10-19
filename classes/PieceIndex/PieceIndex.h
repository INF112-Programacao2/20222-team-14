//
// Created by pedro on 18/10/2022.
//

#ifndef INC_20222_TEAM_14_PIECEINDEX_H
#define INC_20222_TEAM_14_PIECEINDEX_H


class PieceIndex {
private:
    int xPosition;
    int yPosition;
public:
    PieceIndex();
    PieceIndex(int xPosition, int yPosition);

    int getXPosition() const;

    int getYPosition() const;

    void setXPosition(int xPosition);

    void setYPosition(int yPosition);
};


#endif //INC_20222_TEAM_14_PIECEINDEX_H
