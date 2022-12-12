#include <iostream>
#include "./controllers/BoardController/BoardController.h"
#include "interface/interface.h"

using namespace std;

int main() {
    bool newGame = true;
    BoardController *boardController;
    while (newGame) {
        boardController = new BoardController();
        Interface *interface = new Interface(boardController);
        interface->drawBoard();
        cout << "Do you want to play again? (y/n)" << endl;
        char answer;
        cin >> answer;
        if (answer == 'n') {
            newGame = false;
        }
    }
    return 0;
}