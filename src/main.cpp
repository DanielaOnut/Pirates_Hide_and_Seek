#include <iostream>
#include <winbgim.h>
#include <fstream>
#include "functions.cpp"
using namespace std;

ifstream fin("challenge.txt");

/* Daniela */
void putImages ();
void drawBoard ();
void rotateImages ();

/* Denis */
void matrice_challenge(int );

/* Daniela */
int mat[6][6];

int main()
{
    initwindow(900,570,"Pirates Hide and Seek",130,50);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();

    drawBoard();
    rotateImages();

    getch();
    closegraph();
    return 0;
}
