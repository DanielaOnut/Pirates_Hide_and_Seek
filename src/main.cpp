#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "functions.cpp"
#include "LevelsPage.h"
#include "LevelsPage.cpp"
using namespace std;

/* Daniela */
void initializareValori ();
void drawBoard ();
void drawPieces (piesa & );
piesa & clickedOnPiece ();
std::string isPieceInSquare (piesa &);
void movePiece (piesa &);
void updatePage (int &, piesa &);
void mouseEvents ();
void start_game (int);

/* Denis */
void afisare_challenge(int x, int y);
void play_sound();
void desenare_initiala();
bool verificare_solutie(int x);
void matrici_piese();
void btn_finish(int x);
bool clickonFinish();
void castigare_challenge();
int redimensionare_img_ch(char s[]);
bool clickonBACK();

/* Denis + Daniela */
void rotateImages(piesa &piece);
int nrPiesa(piesa &);


int main()
{
    //play_sound();
    initializareValori();
    initwindow(900,590,"Pirates Hide and Seek",160,50);


    LevelsPage levelsPage;
    levelsPage.mouseEvents();

    for (int i = 0; i < 45; ++i) {
        if (i < 10)
            delete vector_imagine[i];
        delete buffer[i];
    }
    getch();
    closegraph();
    return 0;
}
