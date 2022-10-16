class Piece
{
private:
    char name;
    int team;
    int quantMoves;
public:
    Piece(char name, int team);
    ~Piece();

    char getName() const;


    int getTeam() const;

    int getQuantMoves() const;
    void setQuantMoves(int quantMoves);
    void incrementQuantMoves();

    virtual bool checkMove(int xPosition,int  yPosition,int xDest, int yDest);

    virtual bool canKill(Piece &piece,int xPosition,int  yPosition,int xDest, int yDest);
    virtual bool checkPromotion(int xPosition, int yPosition);

};


// PIECE NAMES
// Q = qeen 
// B = bishop
// R = rook
// N = knight
// P = pawn
// K = king


// BOARDS CELLS
// 8  a8 b8 c8 d8 e8 f8 g8 h8
// 7  a7 b7 c7 d7 e7 f7 g7 h7  
// 6  a6 b6 c6 d6 e6 f6 g6 h6
// 5  a5 b5 c5 d5 e5 f5 g5 h5
// 4  a4 b4 c4 d4 e4 f4 g4 h4
// 3  a3 b3 c3 d3 e3 f3 g3 h3
// 2  a2 b2 c2 d2 e2 f2 g2 h2
// 1  a1 b1 c1 d1 e1 f1 g1 h1
//     a  b  c  d  e  f  g  h

// Language: cpp
// Path: Board.h

