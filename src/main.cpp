#include <iostream>
#include <winbgim.h>
#include "functions.cpp"
#include "Menu.h"
#include "Menu.cpp"
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
void drawTimer ();
std::string timeToString ();

/* Denis */
void afisare_challenge(int x, int y);
void play_sound();
void desenare_initiala();
bool verificare_solutie(int x);
void matrici_piese();
bool clickonFinish();
void castigare_challenge();
int redimensionare_img_ch(char s[]);
bool clickonBACK();
bool clickonsound();
void btn_snd();
void rezultate();
bool clickonhint();
bool trans_inminn();
void hint_btn(int g);
/*bool clickonPlay(); // from Menu class
bool clickonRules();
bool clickonExit();*/

/* Denis + Daniela */
void rotateImages(piesa &piece);
int nrPiesa(piesa &);


int main()
{
    initwindow(900,590,"Pirates Hide and Seek",160,50);
    //rezultate();

    Menu menu;
    menu.mouseEvents();

    btn_snd();

    for (int i = 0; i < 45; ++i) {
        if (i < 10)
            delete vector_imagine[i];
        delete buffer[i];
    }
    getch();
    closegraph();
    return 0;
}
