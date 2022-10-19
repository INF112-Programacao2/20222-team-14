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
    ConnectToEngine("stockfish.exe"); 
    string move;
    cin >> move;
    this->position += move + " ";
    string str;
     str = getNextMove(position); 
    cout << "stockfish says" << str << endl;
    CloseConnection();
    PieceIndex *piecePosition = Board::convertPosition(move);
    board->movePiece(piecePosition[0], piecePosition[1], false, false);
    PieceIndex *piecePosition2 = Board::convertPosition(str);
    string res =  board->movePiece(piecePosition2[0], piecePosition2[1], false, false);
   
    if (res != "S") {
        cout << res << endl;
    }
}

void BoardController::checkPromotion() {

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