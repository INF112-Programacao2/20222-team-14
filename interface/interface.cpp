
#include "interface.h"

string Interface::toChessNote (Vector2f p) {
    std::string s = "";
    s += char(p.x / 56 + 97);
    s += char(7 - p.y / 56 + 49);
    return s;
}

Vector2f Interface::toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x, y);
}

void Interface::move(std::string str) {
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);
    int n = board[int(oldPos.y)][int(oldPos.x)];
    board[int(oldPos.y)][int(oldPos.x)] = 0;
    board[int(newPos.y)][int(newPos.x)] = n;
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


void Interface::startGame() {
    Interface interface;
}



Interface::Interface() {
int size = 56;
Vector2f offset(28,28);
std::string position="";

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
    std::string str;
    int n=0; 

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            ////move back//////
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::BackSpace)
                { if (position.length()>6) position.erase(position.length()-6,5); loadPosition();}

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
                  str = toChessNote(oldPos)+toChessNote(newPos);
                  move(str); 
                  if (oldPos!=newPos) position+=str+" ";
                  f[n].setPosition(newPos);                   
                 }                       
        }

       //comp move
       if (Keyboard::isKeyPressed(Keyboard::Space))
       {
        //  str =  getNextMove(position);
                   
         oldPos = toCoord(str[0],str[1]);
         newPos = toCoord(str[2],str[3]);
         
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

        move(str);  position+=str+" ";
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
    }

    // CloseConnection();
}



