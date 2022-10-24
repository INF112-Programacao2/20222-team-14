#include "Board.h"
#include <string>
#include <cstdlib>
#include <stdexcept>


using namespace std;

Board::Board(Board *board) {
    this->cells = new Cell *[8];
    for (int i = 0; i < 8; i++) {
        this->cells[i] = new Cell[8];
        for (int j = 0; j < 8; j++) {
            (this->cells[i])[j] = Cell();
            if (board->getCell(i, j)->isOccupied) {
                int team = board->getCell(i, j)->getPiece()->getTeam();
                if (board->getCell(i, j)->getPiece()->getName() == 'K') {
                    this->cells[i][j].setPiece(new King('K', team));
                } else if (board->getCell(i, j)->getPiece()->getName() == 'Q') {
                    this->cells[i][j].setPiece(new Queen('Q', team));
                } else if (board->getCell(i, j)->getPiece()->getName() == 'R') {
                    this->cells[i][j].setPiece(new Rook('R', team));
                } else if (board->getCell(i, j)->getPiece()->getName() == 'B') {
                    this->cells[i][j].setPiece(new Bishop('B', team));
                } else if (board->getCell(i, j)->getPiece()->getName() == 'N') {
                    this->cells[i][j].setPiece(new Knight('N', team));
                } else if (board->getCell(i, j)->getPiece()->getName() == 'P') {
                    this->cells[i][j].setPiece(new Pawn('P', team));
                }
            }
        }
    }
    this->playerTime = board->playerTime;
}

Board::Board() {
    this->playerTime = 0;
    this->firstMove = true;
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
    PieceIndex *pieceIndex = new PieceIndex[2];
    try {
        string piecePosition = positions.substr(0, 2);
        string destPosition = positions.substr(2, 2);
        int yPiecePosition = 0;
        int xPiecePosition = 0;
        int yDestinationPosition = 0;
        int xDestinationPosition = 0;
        yPiecePosition = (piecePosition[0] - 'a');
        xPiecePosition = 8 - stoi(piecePosition.substr(1, 1));
        yDestinationPosition = (destPosition[0] - 'a');
        xDestinationPosition = 8 - stoi(destPosition.substr(1, 1));
        if (xPiecePosition < 0 || xPiecePosition > 7 || yPiecePosition < 0 || yPiecePosition > 7 ||
            xDestinationPosition < 0 || xDestinationPosition > 7 || yDestinationPosition < 0 ||
            yDestinationPosition > 7) {
            throw invalid_argument("Invalid position");
        }
        pieceIndex[0] = PieceIndex(xPiecePosition, yPiecePosition);
        pieceIndex[1] = PieceIndex(xDestinationPosition, yDestinationPosition);
    } catch (exception e) {
        pieceIndex = nullptr;
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
        if (piece->getName() != 'P') {
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
                if (this->cells[i][yPiecePosition].isOccupied) {
                    return "There is a piece in the way";
                }
            }
        }

        if (abs(yPiecePosition - yDestinationPosition) == abs(xPiecePosition - xDestinationPosition)) {
            int x = xPiecePosition;
            int y = yPiecePosition;
            int xInc = xPiecePosition < xDestinationPosition ? 1 : -1;
            int yInc = yPiecePosition < yDestinationPosition ? 1 : -1;
            while (x != xDestinationPosition && y != yDestinationPosition) {
                x += xInc;
                y += yInc;
                if (this->cells[x][y].isOccupied && x != xDestinationPosition && y != yDestinationPosition) {
                    return "There is a piece in the way";
                }
            }
        }
    }

    // check if the king is in check
    // check if the king is in check after the move
    // check if the king is out of check after the move
    if (!isVirtual) {
//        if (!justCheck) {
//            //check if the king is in check mate
//            if (this->isKingInCheckMate(piece->getTeam())) {
//                return "You are in check mate";
//            }
//        }
        if (this->isKingInCheck(piece->getTeam())) {
            auto *virtualBoard = new Board(this);
            virtualBoard->movePiece(piecePosition, destinationPosition, true, false);
            if (virtualBoard->isKingInCheck(piece->getTeam())) {
                delete virtualBoard;
                return "You can't do that moviment with king in check";
            }
        } else {
            auto *virtualBoard = new Board(this);
            virtualBoard->movePiece(piecePosition, destinationPosition, true, false);
            if (virtualBoard->isKingInCheck(piece->getTeam())) {
                delete virtualBoard;
                return "You can't move a piece witch will put your king in check";
            }
        }
    }

    if (!justCheck) {
        piece->incrementQuantMoves();
        this->cells[xDestinationPosition][yDestinationPosition].setPiece(piece);
        this->cells[xPiecePosition][yPiecePosition].removePiece();
        if (piece->checkPromotion(xDestinationPosition, yDestinationPosition)) {
            return "P";
        }
    }
    return "S";
}

PieceIndex Board::checkPromotion() {
    PieceIndex pieceIndex;
    int row = this->playerTime == 0 ? 7 : 0;
    for (int i = 0; i < 8; i++) {
        if (this->cells[row][i].isOccupied) {
            Piece *piece = this->cells[row][i].getPiece();
            if (piece->getName() == 'P' && piece->getTeam() != this->playerTime) {
                pieceIndex = PieceIndex(0, i);
                return pieceIndex;
            }
        }
    }
    return pieceIndex;
}

void Board::promotePiece(Piece *piece, PieceIndex pieceIndex) {
    this->cells[pieceIndex.getXPosition()][pieceIndex.getYPosition()].setPiece(piece);
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
                if (this->movePiece(pieceIndex, kingIndex, true, true) == "S") {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isKingInCheckMate() {
    int xKingPosition = 0;
    int yKingPosition = 0;
    int team = this->playerTime;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Cell *cell = this->cells[i] + j;
//            if (cell->isOccupied && cell->getPiece()->getName() == 'K' && cell->getPiece()->getTeam() == team) {
//                xKingPosition = i;
//                yKingPosition = j;
//            }
//        }
//    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell *cell = this->cells[i] + j;
            if (cell->isOccupied && cell->getPiece()->getTeam() == team) {
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        if (cell->getPiece()->checkMove(i, j, k, l)) {
                            auto *virtualBoard = new Board(this);
                            virtualBoard->movePiece({i, j}, {k, l}, true, false);
                            if (!virtualBoard->isKingInCheck(team)) {
                                delete virtualBoard;
                                return false;
                            }
                            delete virtualBoard;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::getPlayWithEngin() {
    return playWithEngin;
}

void Board::setPlayWithEngin(bool nPlayWithEngin) {
    this->playWithEngin = nPlayWithEngin;
}

string Board::castling(const string &castlingType) {
    if (castlingType == "e8g8" || castlingType == "e1g1") {
        int row = this->getTurn() == 0 ? 7 : 0;
        if (this->getCell(row, 4)->isOccupied && this->getCell(row, 7)->isOccupied &&
            this->getCell(row, 4)->getPiece()->getQuantMoves() == 0 &&
            this->getCell(row, 7)->getPiece()->getQuantMoves() == 0 &&
            !this->getCell(row, 5)->isOccupied &&
            !this->getCell(row, 6)->isOccupied) {
            auto *virtualBoard = new Board(this);
            for (int i = 4; i < 7; i++) {
                if (virtualBoard->isKingInCheck(this->getTurn())) {
                    delete virtualBoard;
                    return "You can't castling with your king in check";
                }
                virtualBoard->movePiece({row, 4}, {row, i}, true, false);
            }
            delete virtualBoard;
            Piece *rook = this->getCell(row, 7)->getPiece();
            Piece *king = this->getCell(row, 4)->getPiece();
            this->getCell(row, 6)->setPiece(king);
            this->getCell(row, 5)->setPiece(rook);
            this->getCell(row, 4)->removePiece();
            this->getCell(row, 7)->removePiece();
            return "S";
        }
    }
    if (castlingType == "e8c8" || castlingType == "e1c1") {
        int row = this->getTurn() == 0 ? 7 : 0;
        if (this->getCell(row, 4)->getPiece()->getQuantMoves() == 0 &&
            this->getCell(row, 0)->getPiece()->getQuantMoves() == 0 &&
            !this->getCell(row, 1)->isOccupied &&
            !this->getCell(row, 2)->isOccupied &&
            !this->getCell(row, 3)->isOccupied) {
            auto *virtualBoard = new Board(this);
            for (int i = 4; i > 1; i--) {
                if (virtualBoard->isKingInCheck(this->getTurn())) {
                    delete virtualBoard;
                    return "You can't castling with your king in check";
                }
                virtualBoard->movePiece({row, 4}, {row, i}, true, false);
            }
            delete virtualBoard;
            Piece *rook = this->getCell(row, 0)->getPiece();
            Piece *king = this->getCell(row, 4)->getPiece();
            this->getCell(row, 2)->setPiece(king);
            this->getCell(row, 3)->setPiece(rook);
            this->getCell(row, 4)->removePiece();
            this->getCell(row, 0)->removePiece();
            return "S";
        }
    }
    return "Invalid castling";

}

bool Board::getFirstMove() {
    return this->firstMove;
}

void Board::setFirstMove(bool nFirstMove) {
    this->firstMove = nFirstMove;
}

void Board::setPlayerTime(int nPlayerTime) {
    this->playerTime = nPlayerTime;
}

int Board::getPlayerTime() {
    return this->playerTime;
}

void Board::togglePlayerTime() {
    this->playerTime = this->playerTime == 1 ? 0 : 1;
}