#include <iostream>
#include "./controllers/BoardController/BoardController.h"
#include "interface\interface.cpp"
using namespace std;

int main() {
    cout << "Welcome to Chess" << endl;
    bool newGame = true;
    BoardController *boardController;
    while (newGame) {
        boardController = new BoardController();
        boardController->startGame();
        cout << "Do you want to play again? (y/n)" << endl;
        char answer;
        cin >> answer;
        if (answer == 'n') {
            newGame = false;
        }
    }
    return 0;
}