#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "functions.cpp"
using namespace std;

/* Daniela */
void initializareCoord ();
void initialDrawing ();
void drawBoard ();
void drawPieces (piesa & );
piesa & clickedOnPiece ();
std::string pieceToChar (piesa &);
void movePiece (const char *, piesa &);
void updatePage (const char *, int &, piesa &);
void rotateImages (int &, int &);
void mouseEvents ();

/* Denis */
void afisare_challenge(int x);
void play_sound();

/* Daniela */
int mat[6][6];

int main()
{
    play_sound();
    initializareCoord();
    initwindow(900,570,"Pirates Hide and Seek",160,50);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();

    initialDrawing();
    afisare_challenge(4, 0);

    mouseEvents();

    for (int i = 0; i < 30; ++i)
        delete buffer[i];

    getch();
    closegraph();
    return 0;
}
