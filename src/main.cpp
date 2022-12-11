#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "functions.cpp"
using namespace std;

/* Daniela */
void initializareCoord ();
void drawBoard ();
void drawPieces (piesa & );
piesa & clickedOnPiece ();
bool isPieceInSquare (piesa &);
void movePiece (const char *, piesa &);
void updatePage (const char *, int &, piesa &);
void mouseEvents ();

/* Denis */
void afisare_challenge(int x, int y);
void play_sound();
void desenare_initiala();
void verificare_solutie();
void completare_mat_struct();
void matrici_piese();

/* Denis + Daniela*/
void rotateImages(piesa &piece);


int main()
{
    //play_sound();
    initializareCoord();
    initwindow(900,570,"Pirates Hide and Seek",160,50);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();
    desenare_initiala();
    afisare_challenge(1, 0);
    mouseEvents();

    for (int i = 0; i < 45; ++i) {
        if (i < 10)
            delete vector_imagine[i];
        delete buffer[i];
    }
    getch();
    closegraph();
    return 0;
}
