#include <iostream>
#include "BoardController.h"

using namespace std;

BoardController::BoardController() {
    board = new Board();
    this->inGame = true;
}

BoardController::~BoardController() {
    delete board;
}

void BoardController::drawBoard() {

    cout << "     a b c d e f g h" << endl;
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << "    ";
        for (int j = 0; j < 8; j++) {
            Piece *piece = board->getCell(i, j)->getPiece();
            if (piece == nullptr) {
                cout << "  ";
            } else {
                cout << piece->getName() << " ";
            }
        }
        cout << endl;
    }
}

void BoardController::movePiece() {
    cout << "Move piece";
    if (board->getTurn() == 1) {
        cout << " - White Pieces turn" << endl;
    } else {
        cout << " - Black Pieces turn" << endl;
    }
    cout << "Enter the piece position: " << endl;
    string piecePosition;
    cin >> piecePosition;
    cout << "Enter the destination position: " << endl;
    string destinationPosition;
    cin >> destinationPosition;
    board->movePiece(piecePosition, destinationPosition);
}


void BoardController::endGame() {
    this->inGame = false;
    cout << "Game ended" << endl;
    delete board;
}

void BoardController::startGame() {
    do {
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