//
// Created by pedro on 14/10/2022.
//

#ifndef TRABALHOFINAL_KNIGHT_H
#define TRABALHOFINAL_KNIGHT_H


class Knight: public Piece {
public:
    Knight(char name, int team);

    ~Knight();

    bool checkMove(int xPosition, int yPosition, int xDest, int yDest) override;
};

#endif //TRABALHOFINAL_KNIGHT_H
