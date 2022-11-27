#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

/* Daniela */
void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,520);

    setfillstyle(1,COLOR(55,179,192));
    bar(195,65,405,275);
    bar(195,295,405,495);
    bar(425,65,635,275);
    bar(425,295,635,495);
}

/* Daniela */
void rotateImages () {
    int k = 0;
    while(getch()) {
        if (k % 4 == 0) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p1r1.gif",195,65,405,275);
        }
        if (k % 4 == 1) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p1r2.gif",195,65,405,275);
        }
        if (k % 4 == 2) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p1r3.gif",195,65,405,275);
        }
        if (k % 4 == 3) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p1r4.gif",195,65,405,275);
        }
        k++;
    }

    /* Denis */
    k = 0;
    while(getch()) {
        if (k % 4 == 0) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p2r1.gif",195,295,405,495); ///pune imaginea din fisierul resources (imaginea originala) la patratul din coordonatele 195, 295, 405, 495
            ///completeaza patratul din stanga jos
            //Coordonatele patratului se gasesc in functia drawboard, in campurile bar
        }
        if (k % 4 == 1) {
            cleardevice(); ///clears the screen in graphics mode and sets the current position to (0,0). Clearing the screen consists of filling the screen with current background color.
            drawBoard(); ///apel la functia drawboard care deseneaza tabla in fereastra
            readimagefile("resources/p2r2.gif",195,295,405,495);
        }
        if (k % 4 == 2) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p2r3.gif",195,295,405,495);
        }
        if (k % 4 == 3) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p2r4.gif",195,295,405,495);
        }
        k++;
    }

    /* Denis */
    k = 0;
    while(getch()) {
        if (k % 4 == 0) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p3r1.gif",425,65,635,275);
            ///completeaza patratul din dreapta sus
        }
        if (k % 4 == 1) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p3r2.gif",425,65,635,275);
        }
        if (k % 4 == 2) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p3r3.gif",425,65,635,275);
        }
        if (k % 4 == 3) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p3r4.gif",425,65,635,275);
        }
        k++;
    }

    /* Denis */
    k = 0;
    while(getch()) {
        if (k % 4 == 0) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p4r1.gif",425,295,635,495);
            ///completeaza patratul din dreapta jos
        }
        if (k % 4 == 1) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p4r2.gif",425,295,635,495);
        }
        if (k % 4 == 2) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p4r3.gif",425,295,635,495);
        }
        if (k % 4 == 3) {
            cleardevice();
            drawBoard();
            readimagefile("resources/p4r4.gif",425,295,635,495);
        }
        k++;
    }

}

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
