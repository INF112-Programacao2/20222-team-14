#include <iostream>
#include <algorithm>
#include "BoardController.h"

#include "Connector.hpp"

using namespace std;

BoardController::BoardController() {
    board = new Board();
    position = "";
 
    
}

BoardController::~BoardController() {
    delete board;
}

std::string BoardController::getMove() {
    return move;
}

void BoardController::setMove(std::string move) {
    this->move = move;
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
                    char team = piece->getTeam() == 0 ? piece->getName() : (char) tolower(piece->getName());
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
    string rawMove;
    if (move != ""){
    cout << "Make your move "<< endl;
  

    if ((board->getCurrentPlayer() != 0 && board->getPlayWithEngin()) || board->getPlayEnginexEngine()) {
        confirm = true;
         char stoco[] = "stockfish.exe";
        ConnectToEngine(stoco);
        cout << "stockfish sayssss " << position << endl;
        
        move = getNextMove(position);
        cout << "stockfish says " << move << endl;
        CloseConnection();
    } else {
        cout << "Enter the move: "<<endl;
    }
    rawMove = this->handleMove(move);
    // remove last character from rawMove and put the cutted string in move
    if (rawMove.size() == 5) {
        move = rawMove.substr(0, rawMove.size() - 1);
    } else {
        move = rawMove;
    }
    PieceIndex *piecePosition2 = Board::convertPosition(move);
    if ((move == "e1g1" || move == "e8g8" || move == "e1c1" || move == "e8c8") && board->isKing(piecePosition2[0])) {
        res = board->castling(move);
    } else {
        if (piecePosition2 == nullptr) {
            cout << "Invalid move" << endl;
            return;
        }
        res = board->movePiece(piecePosition2[0], piecePosition2[1], false, false);
    }
    if (res == "P") {
        this->PubliccheckPromotion(rawMove.size() == 5 ? rawMove[rawMove.size() - 1] : 'O');
    }
    if (res == "S" || res == "P") {
        this->board->togglePlayerTime();
        this->board->setFirstMove(false);
        this->position += rawMove + " ";
    }
    } else {
        cout << res << endl;
    }
   cout << "sdgsdgsdg";
}
void BoardController::PubliccheckPromotion(char piece){
    this->checkPromotion(piece);
}
void BoardController::setPosition(string s){
    position = s;
}
string BoardController::handleMove(string move) {
    // remove white spaces
    move.erase(remove(move.begin(), move.end(), ' '), move.end());
    if (this->board->getCurrentPlayer() == 0 && move == "0-0") {
        move = "e1g1";
    } else if (this->board->getCurrentPlayer() == 0 && move == "0-0-0") {
        move = "e1c1";
    } else if (this->board->getCurrentPlayer() == 1 && move == "0-0") {
        move = "e8g8";
    } else if (this->board->getCurrentPlayer() == 1 && move == "0-0-0") {
        move = "e8c8";
    }
    return move;
}

void BoardController::checkPromotion(char pieceName = 'O') {
    PieceIndex pieceIndex = this->board->checkPromotion();
    if (pieceIndex.getXPosition() != -1) {
        Piece *piece;
        do {
            cout << "Promote your piece to: " << endl;
            cout << "q - Queen" << endl;
            cout << "r - Rook" << endl;
            cout << "b - Bishop" << endl;
            cout << "n - Knight" << endl;
            int team = this->board->getCurrentPlayer() == 1 ? 1 : 0;
            if (pieceName == 'O') {
                cin >> pieceName;
            }else{
                cout << "stockfish says " << pieceName << endl;
            }
            switch (pieceName) {
                case 'q':
                    piece = new Queen('Q', team);
                    break;
                case 'r':
                    piece = new Rook('R', team);
                    break;
                case 'b':
                    piece = new Bishop('B', team);
                    break;
                case 'n':
                    piece = new Knight('N', team);
                    break;
                default:
                    cout << "Invalid option" << endl;
                    return;
            }
        } while (pieceName != 'q' && pieceName != 'r' && pieceName != 'b' && pieceName != 'n');
        this->board->promotePiece(piece, pieceIndex);

    }
}


void BoardController::endGame() {
    cout << "Game ended" << endl;
    if (this->board->getCurrentPlayer() == 0)
        cout << "Black team won" << endl;
    else
        cout << "White team won" << endl;
    position = "";
    delete board;
}

void BoardController::startGame() {
    cout << "Do you want to play with?: " << endl;
    cout << "1 - Human" << endl;
    cout << "2 - Stockfish" << endl;
    cout << "3 - Stockfish vs Stockfish" << endl;
    char playWithEngin;
    cin >> playWithEngin;
    board->setPlayWithEngin(playWithEngin == '2');
    board->setPlayEnginexEngine(playWithEngin == '3');
    
        cout << endl;
        cout << endl;
        showStatus();
        cout << "----------------------------------" << endl;
}

bool BoardController::verifyCheckMate() {
    return !board->getFirstMove() && board->isKingInCheckMate();
}

void BoardController::showStatus() {
    cout << "Turn: " << board->getTurns() + 1 << endl;
//    TotalPiece totalPieces = board->getTotalPieces();
//    cout << "Total Black Pieces: " << totalPieces.totalBlackPieces;
//    cout << " Total White Pieces: " << totalPieces.totalWhitePieces << endl;
}