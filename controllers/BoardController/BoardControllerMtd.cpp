#include <iostream>
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

    cout << "     a  b  c  d  e  f  g  h" << endl;
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << "    ";
        for (int j = 0; j < 8; j++) {
            Piece *piece = board->getCell(i, j)->getPiece();
            if (piece == nullptr) {
                cout << "   ";
            } else {
                cout << piece->getTeam() << piece->getName() << " ";
            }
        }
        cout << endl;
    }
    cout << "     a  b  c  d  e  f  g  h" << endl;
}

void BoardController::movePiece() {
    cout << "Move piece";
    if (board->getTurn() == 0) {
        cout << " - White Pieces turn" << endl;
    } else {
        cout << " - Black Pieces turn" << endl;
    }
    cout << "Enter the move: ";


    if (board->getTurn() != 0 && board->getPlayWithEngin()) {
        string str;
        ConnectToEngine("stockfish.exe");
        str = getNextMove(position);
        cout << "stockfish says " << position << endl;
        CloseConnection();
        PieceIndex *piecePosition2 = Board::convertPosition(str);
        string res = board->movePiece(piecePosition2[0], piecePosition2[1], false, false);
        if (res == "S")
            this->position += str + " ";
        else
            cout << res << endl;
    } else {
        string move;
        cin >> move;
        PieceIndex *piecePosition = Board::convertPosition(move);
        string res = board->movePiece(piecePosition[0], piecePosition[1], false, false);
        if (res == "S" || res == "P")
            this->position += move + " ";
        else
            cout << res << endl;

        if (res == "P")
            this->checkPromotion();
    }


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
    this->inGame = false;
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
        if (board->isKingInCheckMate()) {
            cout << "Check Mate" << endl;
            endGame();
            break;
        }
        cout << "----------------------------------" << endl;
        drawBoard();
        cout << "----------------------------------" << endl;
        showStatus();
        movePiece();
    } while (!board->isGameOver());
}

void BoardController::showStatus() {
    TotalPiece totalPieces = board->getTotalPieces();
    cout << "Total Black Pieces: " << totalPieces.totalBlackPieces;
    cout << " Total White Pieces: " << totalPieces.totalWhitePieces << endl;
}