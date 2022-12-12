#include "interface.h"
#include <string>
#include <iostream>
using namespace std;
string Interface::toChessNote (Vector2f p) {
    std::string s = "";
    s += char(p.x / 56 + 97);
    s += char(7 - p.y / 56 + 49);
    return s;
}

Vector2f Interface::toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x*56, y*56);
}

void Interface::moveB(std::string str) {
    Vector2f oldPos = toCoord(str[0],str[1]);
    Vector2f newPos = toCoord(str[2],str[3]);

    for(int i=0;i<32;i++)
     if (f[i].getPosition()==newPos) f[i].setPosition(-100,-100);
        
    for(int i=0;i<32;i++)
     if (f[i].getPosition()==oldPos) f[i].setPosition(newPos);

    //castling       //if the king didn't move
    if (str=="e1g1") if (position.find("e1")==-1) moveB("h1f1"); 
    if (str=="e8g8") if (position.find("e8")==-1) moveB("h8f8");
    if (str=="e1c1") if (position.find("e1")==-1) moveB("a1d1");
    if (str=="e8c8") if (position.find("e8")==-1) moveB("a8d8");
}

void Interface::loadPosition() {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
            f[k].setPosition(56 * j, 56 * i);
            k++;
        }
}

// void Interface::promotion(){
    
// }






Interface::Interface(BoardController  *boardController) {
     this->boardController = boardController;
     boardController->startGame();
     move = "";
}
 
void Interface:: moveBack() {
         if (this->position.length()>6)
                 this->position.erase(this->position.length()-6,5);
                 this->loadPosition();
}

void Interface :: drawBoard(){

int size = 56;
Vector2f offset(28,28);
position="";

 RenderWindow window(VideoMode(504, 504), "The Chess! (press SPACE)");

    // ConnectToEngine("stockfish.exe");    

    Texture t1,t2;
    t1.loadFromFile("images/figures.png"); 
    t2.loadFromFile("images/board.png");

    for(int i=0;i<32;i++) f[i].setTexture(t1);
    Sprite sBoard(t2); 

    loadPosition();

    bool isMove=false;
    float dx=0, dy=0;
    Vector2f oldPos,newPos;
    int n=0; 

   do{
    
      
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            ////move back//////
                  if (e.type == Event::KeyPressed)
                         if (e.key.code == Keyboard::BackSpace)
                { 
                    moveBack();
                 }

            /////drag and drop///////
            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                  for(int i=0;i<32;i++)
                  if (f[i].getGlobalBounds().contains(pos.x,pos.y))
                      {
                       isMove=true;
                        n=i;
                       dx=pos.x - f[i].getPosition().x;
                       dy=pos.y - f[i].getPosition().y;
                       oldPos  =  f[i].getPosition();
                    
                      }

             if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Left)
                 {
                  isMove=false;
                  Vector2f p = f[n].getPosition() + Vector2f(size/2,size/2);
                  newPos = Vector2f( size*int(p.x/size), size*int(p.y/size) );
       
                    if (boardController->verifyCheckMate()) {
                        cout << "Check Mate" << endl;
                        boardController->endGame();
                        // break;
                    }
                    move = toChessNote(oldPos)+toChessNote(newPos);
                    if (move != "" && boardController->getMove() != move) {
                        this->boardController->setMove(move);
                        boardController->movePiece();
                        cout << "Move: " << move << endl;
                        if (boardController->res == "S" || boardController->res == "P") {
                            moveB(move);
                            if (oldPos!=newPos) 
                            position+=move+" ";
                            f[n].setPosition(newPos);  
                        }else {
                            cout <<boardController->res << endl;
                            move = "";
                            this->boardController->setMove(move);
                            f[n].setPosition(oldPos); 
                        }
                    } 
                 }       
                         
        }

       //comp move
       if (Keyboard::isKeyPressed(Keyboard::Space))
       {
        //  str =  getNextMove(position);
                   
         oldPos = toCoord(move[0],move[1]);
         newPos = toCoord(move[2],move[3]);
         
         for(int i=0;i<32;i++) if (f[i].getPosition()==oldPos) n=i;
         
         /////animation///////
         for(int k=0;k<50;k++)
          {
            Vector2f p = newPos - oldPos;
            f[n].move(p.x/50, p.y/50); 
            window.draw(sBoard);
            for(int i=0;i<32;i++) f[i].move(offset);
            for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
            for(int i=0;i<32;i++) f[i].move(-offset);
            window.display();
          }

        moveB(move);  position+=move+" ";
        f[n].setPosition(newPos); 
        }

        if (isMove) f[n].setPosition(pos.x-dx,pos.y-dy);

    ////// draw  ///////
    window.clear();
    window.draw(sBoard);
    for(int i=0;i<32;i++) f[i].move(offset);
    for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
    for(int i=0;i<32;i++) f[i].move(-offset);
    window.display();
    }while (window.isOpen());
    // CloseConnection();
}



