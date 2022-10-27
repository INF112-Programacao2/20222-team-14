#include <iostream>
#include <iomanip>
#include "BoardController.h"
#include "Connector.hpp"

using namespace std;

BoardController::BoardController() {
    board = new Board();
    this->inGame = true;
}

BoardController::~BoardController() {
    delete board;
}

void BoardController::drawBoard() {
//    cout << "a    b    c    d    e    f    g    h" << endl;
    cout << "+---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 8; i++) {
        {
//            cout << 8 - i << " ";
            for (int j = 0; j < 8; j++) {
                Piece *piece = board->getCell(i, j)->getPiece();
                if (piece != nullptr) {
                    char team = piece->getTeam()==0? piece->getName(): (char) tolower(piece->getName());
                    cout << "| " << team << " ";
                } else {
                    cout << "|   ";
                }
            }
            cout << "|  " << 8 - i << endl;
            cout << "+---+---+---+---+---+---+---+---+" << endl;
        }
    }
    cout << "  a   b   c   d   e   f   g   h" << endl;
//    for (int i = 0; i < 8; i++) {
//        cout << 8 - i << "    ";
//        for (int j = 0; j < 8; j++) {
//            Piece *piece = board->getCell(i, j)->getPiece();
//            if (piece == nullptr) {
//                cout << "   ";
//            } else {
//                cout << piece->getTeam() << piece->getName() << " ";
//            }
//        }
//        cout << "   " << 8 - i;
//        //set cout to print the board
//        cout << endl;
//    }
//    cout << "     a  b  c  d  e  f  g  h" << endl;
}

void BoardController::movePiece() {
    string res;
    string move;
    cout << "Make your move ";
    if (board->getTurn() == 0) {
        cout << " - White Pieces turn" << endl;
    } else {
        cout << " - Black Pieces turn" << endl;
    }
    if (board->getTurn() != 0 && board->getPlayWithEngin()) {
        ConnectToEngine("stockfish.exe");
        move = getNextMove(position);
        cout << "stockfish says " << move << endl;
        CloseConnection();
    } else {
        cout << "Enter the move: ";
        cin >> move;
    }
    move = this->handleMove(move);
    if (move == "e1g1" || move == "e8g8" || move == "e1c1" || move == "e8c8") {
        res = board->castling(move);
    } else {
        PieceIndex *piecePosition2 = Board::convertPosition(move);
        if (piecePosition2 == nullptr) {
            cout << "Invalid move" << endl;
            return;
        }
        res = board->movePiece(piecePosition2[0], piecePosition2[1], false, false);
    }
    if (res == "P") {
        this->checkPromotion();
    }
    if (res == "S" || res == "P") {
        this->board->togglePlayerTime();
        this->board->setFirstMove(false);
        this->position += move + " ";
    } else {
        cout << res << endl;
    }
}

string BoardController::handleMove(string move) {
    if (this->board->getTurn() == 0 && move == "0-0") {
        move = "e1g1";
    } else if (this->board->getTurn() == 0 && move == "0-0-0") {
        move = "e1c1";
    } else if (this->board->getTurn() == 1 && move == "0-0") {
        move = "e8g8";
    } else if (this->board->getTurn() == 1 && move == "0-0-0") {
        move = "e8c8";
    }
    return move;
}

void BoardController::checkPromotion() {
    PieceIndex pieceIndex = this->board->checkPromotion();
    if (pieceIndex.getXPosition() != -1) {
        char pieceName;
        Piece *piece;
        do {
            cout << "Promote your piece to: " << endl;
            cout << "1 - Queen" << endl;
            cout << "2 - Rook" << endl;
            cout << "3 - Bishop" << endl;
            cout << "4 - Knight" << endl;
            int team = this->board->getTurn() == 0 ? 1 : 0;
            cin >> pieceName;
            switch (pieceName) {
                case '1':
                    piece = new Queen('Q', team);
                    break;
                case '2':
                    piece = new Rook('R', team);
                    break;
                case '3':
                    piece = new Bishop('B', team);
                    break;
                case '4':
                    piece = new Knight('K', team);
                    break;
                default:
                    cout << "Invalid option" << endl;
                    return;
            }
        } while (pieceName != '1' && pieceName != '2' && pieceName != '3' && pieceName != '4');
        this->board->promotePiece(piece, pieceIndex);

    }
}


void BoardController::endGame() {
    cout << "Game ended" << endl;
    if (this->board->getTurn() == 0)
        cout << "Black team won" << endl;
    else
        cout << "White team won" << endl;
    delete board;
}

void BoardController::startGame() {
    cout << "Do you want to play with the engin? (y/n): ";
    char playWithEngin;
    cin >> playWithEngin;
    board->setPlayWithEngin(playWithEngin == 'y');
    do {
        cout << endl;
        drawBoard();
        cout << endl;
        showStatus();
        cout << "----------------------------------" << endl;
        if (this->verifyCheckMate()) {
            cout << "Check Mate" << endl;
            endGame();
            break;
        }
        movePiece();
    } while (!board->isGameOver());
}

bool BoardController::verifyCheckMate() {
    return !board->getFirstMove() && board->isKingInCheckMate();
}

void BoardController::showStatus() {
    TotalPiece totalPieces = board->getTotalPieces();
    cout << "Total Black Pieces: " << totalPieces.totalBlackPieces;
    cout << " Total White Pieces: " << totalPieces.totalWhitePieces << endl;
}