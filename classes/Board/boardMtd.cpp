#include "Board.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Board::Board(Board const &board) {
    this->cells = new Cell *[8];
    for (int i = 0; i < 8; i++) {
        this->cells[i] = new Cell[8];
        for (int j = 0; j < 8; j++) {
            this->cells[i][j] = board.cells[i][j];
        }
    }
    this->playerTime = board.playerTime;
}

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

string
verifyMove(Piece *piece, int xPiecePosition, int yPiecePosition, int xDestinationPosition, int yDestinationPosition) {
    if (!piece->checkMove(xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition)) {
        return "Invalid move for that piece";
    }
    return "S";
}

string verifyKill(Piece *piece, Piece *destPiece, int xPiecePosition, int yPiecePosition, int xDestinationPosition,
                  int yDestinationPosition) {
    if (!piece->canKill(*destPiece, xPiecePosition,
                        yPiecePosition, xDestinationPosition, yDestinationPosition)) {
        return "You can't kill that piece";
    }
    return "S";
}

PieceIndex *Board::convertPosition(const string &positions) {
    string piecePosition = positions.substr(0, 2);
    string destPosition = positions.substr(2, 2);
    PieceIndex *pieceIndex = new PieceIndex[2];
    int yPiecePosition = 0;
    int xPiecePosition = 0;
    int yDestinationPosition = 0;
    int xDestinationPosition = 0;
    try {
        yPiecePosition = (piecePosition[0] - 'a');
        xPiecePosition = 8 - stoi(piecePosition.substr(1, 1));
        yDestinationPosition = (destPosition[0] - 'a');
        xDestinationPosition = 8 - stoi(destPosition.substr(1, 1));
        pieceIndex[0] = PieceIndex(xPiecePosition, yPiecePosition);
        pieceIndex[1] = PieceIndex(xDestinationPosition, yDestinationPosition);
    } catch (exception e) {
        pieceIndex[0] = PieceIndex(-1, -1);
        pieceIndex[1] = PieceIndex(-1, -1);
    }
    return pieceIndex;
}

string
Board::movePiece(PieceIndex piecePosition, PieceIndex destinationPosition, bool isVirtual = false,
                 bool justCheck = false) {

    int xPiecePosition = piecePosition.getXPosition();
    int yPiecePosition = piecePosition.getYPosition();
    int xDestinationPosition = destinationPosition.getXPosition();
    int yDestinationPosition = destinationPosition.getYPosition();
//    cout << xPiecePosition << " " << yPiecePosition << " " << xDestinationPosition << " " << yDestinationPosition << endl;

    if (xPiecePosition < 0 || xPiecePosition > 7 || yPiecePosition < 0 || yPiecePosition > 7 ||
        xDestinationPosition < 0 || xDestinationPosition > 7 || yDestinationPosition < 0 || yDestinationPosition > 7) {
        return "Invalid position";
    }

    bool isOccupied = this->cells[xPiecePosition][yPiecePosition].isOccupied;
    if (!isOccupied) {
        return "There is no piece in this position";
    }

    Piece *piece = this->cells[xPiecePosition][yPiecePosition].getPiece();
    Piece *destPiece = nullptr;
    if (this->cells[xDestinationPosition][yDestinationPosition].isOccupied) {
        destPiece = this->cells[xDestinationPosition][yDestinationPosition].getPiece();
    }
    if (this->getTurn() != piece->getTeam() && !justCheck) {
        return "You are trying to move a enemy piece";
    }

    if (this->cells[xDestinationPosition][yDestinationPosition].isOccupied) {
        Piece *dPiece = this->cells[xDestinationPosition][yDestinationPosition].getPiece();
        if (dPiece != nullptr && piece->getTeam() == dPiece->getTeam()) {
            return "You can't kill your own piece";
        }
    }
    string res = verifyMove(piece, xPiecePosition, yPiecePosition, xDestinationPosition, yDestinationPosition);
    if (destPiece != nullptr) {
        string killRes = verifyKill(piece, destPiece, xPiecePosition, yPiecePosition, xDestinationPosition,
                                    yDestinationPosition);
        if (destPiece->getName() != 'P') {
            if (res == "S") {
                if (killRes != "S") {
                    return killRes;
                }
            } else {
                return res;
            }
        } else {
            if (killRes != "S") {
                return killRes;
            }
        }
    } else {
        if (res != "S") {
            return res;
        }
    }


    if (xPiecePosition == xDestinationPosition && yPiecePosition == yDestinationPosition) {
        return "You can't move to the same position";
    }

    if (piece->getName() != 'K') {
        if (xPiecePosition == xDestinationPosition) {
            for (int i = min(yPiecePosition, yDestinationPosition) + 1;
                 i < max(yPiecePosition, yDestinationPosition); i++) {
                if (this->cells[xPiecePosition][i].isOccupied) {
                    return "There is a piece in the ways";
                }
            }
        }

        if (yPiecePosition == yDestinationPosition) {
            for (int i = min(xPiecePosition, xDestinationPosition) + 1;
                 i < max(xPiecePosition, xDestinationPosition); i++) {
                cout << i << " --- " << max(xPiecePosition, xDestinationPosition) << endl;
                if (this->cells[i][yPiecePosition].isOccupied) {
                    return "There is a piece in the way";
                }
            }
        }

        if (abs(yPiecePosition - yDestinationPosition) == abs(xPiecePosition - xDestinationPosition)) {
            for (int i = min(xPiecePosition, xDestinationPosition) + 1;
                 i < max(xPiecePosition, xDestinationPosition); i++) {
                int s = xPiecePosition + yPiecePosition;
                int j = abs(i - s);
                if (this->cells[i][j].isOccupied) {
                    return "There is a piece in the way";
                }
            }
        }
    }

    // check if the king is in check
    // check if the king is in check after the move
    // check if the king is out of check after the move
    if (!isVirtual) {
        if (this->isKingInCheck(piece->getTeam())) {
            auto *virtualBoard = new Board(*this);
            virtualBoard->movePiece(piecePosition, destinationPosition, true, false);
            if (virtualBoard->isKingInCheck(piece->getTeam())) {
                delete virtualBoard;
                return "You can't move that piece with king in check";
            }
        } else {
            auto *virtualBoard = new Board(*this);
            virtualBoard->movePiece(piecePosition, destinationPosition, true, false);
            if (virtualBoard->isKingInCheck(piece->getTeam())) {
                delete virtualBoard;
                return "You can't move a piece witch will put your king in check";
            }
        }
    }

    //check if the king is in check mate
//    if (this->isKingInCheckMate(piece->getTeam())) {
//        cout << "You are in check mate" << endl;
//        return;
//    }

    if (!justCheck) {
        piece->incrementQuantMoves();
        this->cells[xDestinationPosition][yDestinationPosition].setPiece(piece);
        this->cells[xPiecePosition][yPiecePosition].removePiece();
        this->playerTime = this->playerTime == 1 ? 0 : 1;
        if (piece->checkPromotion(xDestinationPosition, yDestinationPosition)) {
            this->promotePiece(piece, xDestinationPosition, yDestinationPosition);
        }
    }
    return "S";
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell *cell = this->cells[i] + j;
            if (cell->isOccupied && cell->getPiece()->getTeam() == 1) {
                totalWhitePieces++;
            } else if (cell->isOccupied && cell->getPiece()->getTeam() == 0) {
                totalBlackPieces++;
            }
        }
    }
    return {totalBlackPieces, totalWhitePieces};
}

bool Board::isKingInCheck(int team) {
    int xKingPosition = 0;
    int yKingPosition = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell *cell = this->cells[i] + j;
            if (cell->isOccupied && cell->getPiece()->getName() == 'K' && cell->getPiece()->getTeam() == team) {
                xKingPosition = i;
                yKingPosition = j;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell *cell = this->cells[i] + j;
            if (cell->isOccupied && cell->getPiece()->getTeam() != team) {
                PieceIndex pieceIndex = {i, j};
                PieceIndex kingIndex = {xKingPosition, yKingPosition};
                if (this->movePiece(pieceIndex, kingIndex, true, true) == "S" &&
                    cell->getPiece()->checkMove(i, j, xKingPosition, yKingPosition)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isKingInCheckMate(int team) {
//    int xKingPosition = 0;
//    int yKingPosition = 0;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Cell *cell = this->cells[i] + j;
//            if (cell->isOccupied && cell->getPiece()->getName() == 'K' && cell->getPiece()->getTeam() == team) {
//                xKingPosition = i;
//                yKingPosition = j;
//            }
//        }
//    }
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Cell *cell = this->cells[i] + j;
//            if (cell->isOccupied && cell->getPiece()->getTeam() == team) {
//                for (int k = 0; k < 8; k++) {
//                    for (int l = 0; l < 8; l++) {
//                        if (cell->getPiece()->checkMove(i, j, k, l)) {
//                            auto *virtualBoard = new Board(*this);
//                            virtualBoard->movePiece({i, j}, {k, l}, true);
//                            if (!virtualBoard->isKingInCheck(team)) {
//                                delete virtualBoard;
//                                return false;
//                            }
//                            delete virtualBoard;
//                        }
//                    }
//                }
//            }
//        }
//    }
    return true;
}