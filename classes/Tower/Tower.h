
#include "../Piece/Piece.h"
class Tower : public Piece {
public:
    Tower(char name, int team);
    ~Tower();

    bool checkMove(int xPosition,int  yPosition,int xDest, int yDest) override;
};