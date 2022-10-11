#include "../cell/Cell.h"
class Board
{
private:
    Piece **pieces;
    bool inGame;

public:
    Board()
    {
        this->pieces = new Piece *[8];
        for (int i = 0; i < 8; i++)
        {
            this->pieces[i] = new Piece[8];
            for(int j = 0; j < 8; j++){
                this->pieces[i][j] = Piece(i, j);
            }

        }
    };
    ~Board();
};
