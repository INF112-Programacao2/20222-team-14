#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board() {
    this->playerTime = 0;
    this->cells = new Cell *[8];
    for (int i = 0; i < 8; i++) {
        this->cells[i] = new Cell[8];
        for (int j = 0; j < 8; j++) {
            this->cells[i][j] = Cell();
            if (i == 1 || i == 6) {
                this->cells[i][j].setPiece(new Pawn('P', i == 1 ? 1 : 0));
            }

            if (i == 0 || i == 7) {
                switch (j) {
                    case 0:
                    case 7:
                        this->cells[i][j].setPiece(new Rook('R', i == 0 ? 1 : 0));
                        break;
                    case 1:
                    case 6:
                        this->cells[i][j].setPiece(new Knight('N', i == 0 ? 1 : 0));
                        break;
                    case 2:
                    case 5:
                        this->cells[i][j].setPiece(new Bishop('B', i == 0 ? 1 : 0));
                        break;
                    case 3:
                        this->cells[i][j].setPiece(new Queen('Q', i == 0 ? 1 : 0));
                        break;
                    case 4:
                        this->cells[i][j].setPiece(new King('K', i == 0 ? 1 : 0));
                        break;
                }
            }
        }
    }
}

Board::~Board() {
    delete cells;
}

bool
verifyMove(Piece *piece, int xPiecePosition, int yPiecePosition, int xDestinationPosition, int yDestinationPosition) {
    if (!piece->checkMove(xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition)) {
        cout << "Invalid move for that piece" << endl;
        return false;
    }
    return true;
}

bool verifyKill(Piece *piece, Piece *destPiece, int xPiecePosition, int yPiecePosition, int xDestinationPosition,
                int yDestinationPosition) {
    if (!piece->canKill(*destPiece, xPiecePosition,
                        yPiecePosition, xDestinationPosition, yDestinationPosition)) {
        cout << "You can't kill that piece" << endl;
        return false;
    }
    return true;
}

void Board::movePiece(string piecePosition, string destinationPosition) {
    if (piecePosition.length() != 2 || destinationPosition.length() != 2) {
        cout << "Invalid position" << endl;
        return;
    }
    int yPiecePosition = 0;
    int xPiecePosition = 0;
    int yDestinationPosition = 0;
    int xDestinationPosition = 0;
    try {
        yPiecePosition = (piecePosition[0] - 'a');
        xPiecePosition = 8 - stoi(piecePosition.substr(1, 1));
        xDestinationPosition = 8 - stoi(destinationPosition.substr(1, 1));
        yDestinationPosition = (destinationPosition[0] - 'a');
    } catch (exception e) {
        cout << "Invalid position" << endl;
        return;
    }

//    cout << xPiecePosition << " " << yPiecePosition << " " << xDestinationPosition << " " << yDestinationPosition << endl;

    if (xPiecePosition < 0 || xPiecePosition > 7 || yPiecePosition < 0 || yPiecePosition > 7 ||
        xDestinationPosition < 0 || xDestinationPosition > 7 || yDestinationPosition < 0 || yDestinationPosition > 7) {
        cout << "Invalid position" << endl;
        return;
    }

    bool isOccupied = this->cells[xPiecePosition][yPiecePosition].isOccupied;
    if (!isOccupied) {
        cout << "There is no piece in this position" << endl;
        return;
    }

    Piece *piece = this->cells[xPiecePosition][yPiecePosition].getPiece();
    Piece *destPiece = nullptr;
    if (this->cells[xDestinationPosition][yDestinationPosition].isOccupied) {
        destPiece = this->cells[xDestinationPosition][yDestinationPosition].getPiece();
    }
    cout << this->getTurn() << " -- " << piece->getTeam() << endl;
    if (this->getTurn() != piece->getTeam()) {
        cout << "You are trying to move a enemy piece" << endl;
        return;
    }

    if (this->cells[xDestinationPosition][yDestinationPosition].isOccupied) {
        Piece *dPiece = this->cells[xDestinationPosition][yDestinationPosition].getPiece();
        if (dPiece != nullptr && piece->getTeam() == dPiece->getTeam()) {
            cout << "You can't kill your own piece" << endl;
            return;
        }
    }
    if (destPiece != nullptr) {
        if (destPiece->getName() != 'P') {
            if (verifyMove(piece, xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition)) {
                if (!verifyKill(piece, destPiece, xPiecePosition, yPiecePosition, xDestinationPosition,
                                yDestinationPosition)) {
                    return;
                }
            } else {
                return;
            }
        } else {
            if (!verifyKill(piece, destPiece, xPiecePosition, yPiecePosition, xDestinationPosition,
                            yDestinationPosition)) {
                return;
            }
        }
    } else {
        if (!verifyMove(piece, xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition)) {
            return;
        }
    }


    if (xPiecePosition == xDestinationPosition && yPiecePosition == yDestinationPosition) {
        cout << "You can't move to the same position" << endl;
        return;
    }

    if (piece->getName() != 'K') {
        if (xPiecePosition == xDestinationPosition) {
            for (int i = min(yPiecePosition, yDestinationPosition) + 1;
                 i < max(yPiecePosition, yDestinationPosition); i++) {
                if (this->cells[xPiecePosition][i].isOccupied) {
                    cout << "There is a piece in the ways" << endl;
                    return;
                }
            }
        }

        if (yPiecePosition == yDestinationPosition) {
            for (int i = min(xPiecePosition, xDestinationPosition) + 1;
                 i < max(xPiecePosition, xDestinationPosition); i++) {
                cout << i << " --- " << max(xPiecePosition, xDestinationPosition) << endl;
                if (this->cells[i][yPiecePosition].isOccupied) {
                    cout << "There is a piece in the way" << endl;
                    return;
                }
            }
        }

        if (yPiecePosition - xPiecePosition == yDestinationPosition - xDestinationPosition) {
            for (int i = min(xPiecePosition, xDestinationPosition) + 1;
                 i < max(xPiecePosition, xDestinationPosition); i++) {
                if (this->cells[i][i - xPiecePosition + yPiecePosition].isOccupied) {
                    cout << "There is a piece in the way" << endl;
                    return;
                }
            }
        }
    }
    piece->incrementQuantMoves();
    this->cells[xDestinationPosition][yDestinationPosition].setPiece(piece);
    this->cells[xPiecePosition][yPiecePosition].removePiece();
    cout << "Moved " << piece->getQuantMoves() << endl;
    this->playerTime = this->playerTime == 1 ? 0 : 1;
    if (piece->checkPromotion(xDestinationPosition, yDestinationPosition)) {
        this->promotePiece(piece, xDestinationPosition, yDestinationPosition);
    }

}

void Board::promotePiece(Piece *piece, int xDestinationPosition, int yDestinationPosition) {
    char pieceName;
    do {
        cout << "Promote your piece to: " << endl;
        cout << "1 - Queen" << endl;
        cout << "2 - Rook" << endl;
        cout << "3 - Bishop" << endl;
        cout << "4 - Knight" << endl;
        cin >> pieceName;
        switch (pieceName) {
            case '1':
                piece = new Queen('Q', piece->getTeam());
                break;
            case '2':
                piece = new Rook('R', piece->getTeam());
                break;
            case '3':
                piece = new Bishop('B', piece->getTeam());
                break;
            case '4':
                piece = new Knight('K', piece->getTeam());
                break;
            default:
                cout << "Invalid option" << endl;
                return;
        }
    } while (pieceName != '1' && pieceName != '2' && pieceName != '3' && pieceName != '4');
    this->cells[xDestinationPosition][yDestinationPosition].setPiece(piece);
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