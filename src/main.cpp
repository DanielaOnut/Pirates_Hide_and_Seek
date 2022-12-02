#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "functions.cpp"
using namespace std;

/* Daniela */
void initialDrawing ();
void putImages ();
void drawBoard ();
void drawPieces (piesa & );
piesa & clickedOnPiece ();
const std::string pieceToChar (piesa &);
void movePiece (const char *, piesa &);
void updatePage (const char *, int &, piesa &);
void rotateImages (int &, int &);

void waitForMouseClick () { while (!ismouseclick(WM_LBUTTONDOWN)) { delay (100);} }

/* Denis */
void afisare_challenge(int x);

/* Daniela */
int mat[6][6];

int main()
{
    initwindow(900,570,"Pirates Hide and Seek",160,50);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();
    afisare_challenge(8);
    initialDrawing();

    waitForMouseClick();
    clearmouseclick(WM_LBUTTONDOWN);
    piesa & piece = clickedOnPiece();
    if (piece.x1 != -1) { // am dat click pe o piesa
        cout << "clickedOnPiece\n";
        std::string pieceName = pieceToChar(piece);
        //std::cout << pieceName.c_str() << '\n';
        while (!ismouseclick(WM_LBUTTONUP))
        {
            movePiece(pieceName.c_str(),piece);
        }
        clearmouseclick(WM_LBUTTONUP);
    }

    for (int i = 0; i < 30; ++i)
        delete buffer[i];

    getch();
    closegraph();
    return 0;
}
