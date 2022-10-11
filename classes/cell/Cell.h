#include "..\Piece\Piece.h"
class Cell
{
private:
    int x;
    int y;  
    Piece *piece;
public:
    Cell(int x, int y);
    Cell();
    ~Cell();
    
};