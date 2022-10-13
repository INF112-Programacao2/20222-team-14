#include "Board.h"
#include <iostream>
#include <string>
using namespace std;

Board::Board() {
    this->playerTime = 1;
    this->cells = new Cell *[8];
    for (int i = 0; i < 8; i++) {
        this->cells[i] = new Cell[8];
        for (int j = 0; j < 8; j++) {
            this->cells[i][j] = Cell();
            if (i == 1 || i == 6) {
                this->cells[i][j].setPiece(new Piece('P', i == 1 ? 1 : 0));
            }

            if (i == 0 || i == 7) {
                switch (j) {
                    case 0:
                    case 7:
                        this->cells[i][j].setPiece(new Tower('R', i == 0 ? 1 : 0));
                        break;
                    case 1:
                    case 6:
                        this->cells[i][j].setPiece(new Piece('N', i == 0 ? 1 : 0));
                        break;
                    case 2:
                    case 5:
                        this->cells[i][j].setPiece(new Bishop('B', i == 0 ? 1 : 0));
                        break;
                    case 3:
                        this->cells[i][j].setPiece(new Piece('Q', i == 0 ? 1 : 0));
                        break;
                    case 4:
                        this->cells[i][j].setPiece(new Piece('K', i == 0 ? 1 : 0));
                        break;
                }
            }
        }
    }
}

Board::~Board() {
    delete this;
}

void Board::movePiece(string piecePosition, string destinationPosition) {
    if (piecePosition.length() != 2 || destinationPosition.length() != 2) {
        cout << "Invalid position" << endl;
        return;
    }

    int yPiecePosition = (piecePosition[0] - 'a') ;
    int xPiecePosition = 8-stoi(piecePosition.substr(1, 1));
    int xDestinationPosition = 8-stoi(destinationPosition.substr(1, 1));
    int yDestinationPosition = (destinationPosition[0] - 'a') ;

//    cout << xPiecePosition << " " << yPiecePosition << " " << xDestinationPosition << " " << yDestinationPosition << endl;

    if (xPiecePosition < 0 || xPiecePosition > 7 || yPiecePosition < 0 || yPiecePosition > 7 ||
        xDestinationPosition < 0 || xDestinationPosition > 7 || yDestinationPosition < 0 || yDestinationPosition > 7) {
        cout << "Invalid position" << endl;
        return;
    }

    bool isOccupied= this->cells[xPiecePosition][yPiecePosition].isOccupied;
    if (!isOccupied) {
        cout << "There is no piece in this position" << endl;
        return;
    }

    Piece *piece = this->cells[xPiecePosition][yPiecePosition].getPiece();
    if(!piece->checkMove(xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition)){
        cout << "Invalid move for that piece" << endl;
        return;
    }

    if(this->cells[xDestinationPosition][yDestinationPosition].isOccupied){
        Piece *dPiece = this->cells[xDestinationPosition][yDestinationPosition].getPiece();
        if(dPiece != nullptr && piece->getTeam() == dPiece->getTeam()){
            cout << "You can't kill your own piece" << endl;
            return;
        }
    }

    if(xPiecePosition == xDestinationPosition && yPiecePosition == yDestinationPosition){
        cout << "You can't move to the same position" << endl;
        return;
    }

    if(xPiecePosition == xDestinationPosition){
        for(int i = min(yPiecePosition, yDestinationPosition)+1; i < max(yPiecePosition, yDestinationPosition); i++){
            if(this->cells[xPiecePosition][i].isOccupied){
                cout << "There is a piece in the way" << endl;
                return;
            }
        }
    }

    if(yPiecePosition == yDestinationPosition){
        for(int i = min(xPiecePosition, xDestinationPosition)+1; i < max(xPiecePosition, xDestinationPosition); i++){
            if(this->cells[i][yPiecePosition].isOccupied){
                cout << "There is a piece in the way" << endl;
                return;
            }
        }
    }

    if(yPiecePosition - xPiecePosition == yDestinationPosition - xDestinationPosition){
        for(int i = min(xPiecePosition, xDestinationPosition)+1; i < max(xPiecePosition, xDestinationPosition); i++){
            if(this->cells[i][i - xPiecePosition + yPiecePosition].isOccupied){
                cout << "There is a piece in the way" << endl;
                return;
            }
        }
    }

    this->cells[xDestinationPosition][yDestinationPosition].setPiece(piece);
    this->cells[xPiecePosition][yPiecePosition].setPiece(nullptr);
    this->playerTime = this->playerTime == 1 ? 2 : 1;


}

bool Board::isGameOver() {
    return false;
}

Cell *Board::getCell(int x, int y) {
    Cell *cell = (this->cells[x]) + y;
    return cell;
}

int Board::getTurn() {
    return this->playerTime;
}

TotalPiece Board::getTotalPieces() {
    int totalWhitePieces = 0;
    int totalBlackPieces = 0;
//    for(int i = 0; i < 8; i++) {
//        for(int j = 0; j < 8; j++) {
//            Cell *cell = this->cells[i]+j;
//            if(cell->isOccupied && cell->getPiece()->getTeam() == 1) {
//                totalWhitePieces++;
//            }else if(cell->isOccupied && cell->getPiece()->getTeam() == 0) {
//                totalBlackPieces++;
//            }
//        }
//    }
    return {totalBlackPieces, totalWhitePieces};
}