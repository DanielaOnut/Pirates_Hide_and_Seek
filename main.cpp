#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
using namespace std;

ifstream fin("challenge.txt");

/* Daniela */
void putImages ();

void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,530);

    setfillstyle(1,COLOR(71,179,192));
    bar(195,65,405,275);
    bar(195,295,405,505);
    bar(425,65,635,275);
    bar(425,295,635,505);

    putImages();
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


/* Denis */
void matrice_challenge(int i) /// i va fi linia din matrice (pe care se afla elementele care alcatuiesc un challenge)
{
    /* Legenda
    100 - butoi
    101 - corabie scufundata
    102 - corabie_panzealbe
    103 - cufar
    104 - caracatita
    105 - castel
    106 - stanca
    107 - corabie_panzenegre
    -1 - element vid
    */
    ///Nivele disponibile: Starter, Junior, Expert, Master
    //Challenge 1 - starter
    //Challenge 2 - starter
    //Challenge 3 - starter
    //Challenge 4 - starter
    //Challenge 5 - junior
    //Challenge 6 - junior
    //Challenge 7 - expert
    //Challenge 8 - expert
    //Challenge 9 - master
    //Challenge 10 - master

    /*
    Challenge 1 - 4 corabii cu panze negre, rosu orientat spre nord
                    107 107 107 107 -1 -1 -1
    Challenge 2 - 3 corabii cu panze albe si o caracatita, rosu orientat spre sud
                    102 102 102 104 -1 -1 -1
    Challenge 3 - 2 corabii scufundate, 2 butoaie, un castel, rosu orientat spre nord
                    101 101 100 100 105 -1 -1
    Challenge 4 - o corabie panza negre, un butoi, un cufar, doua caracatite, rosu orientat spre sud
                    107 100 103 104 104 -1 -1
    Challenge 5 - o corabie panze negre, un cufar
                    107 103 -1 -1 -1 -1 -1
    Challenge 6 - doua corabii scufundate, o caractita, 3 corabii cu panze negre, o corabie cu panze albe
                    101 101 104 107 107 107 102
    Challenge 7 - doua corabii cu panze negre, un butoi, o stanca
                    107 107 100 106 -1 -1 -1
    Challenge 8 - o corabie scufundata, o caracatita, trei cufere, doua castele
                    101 104 103 103 103 105 105
    Challenge 9 - 2 corabii cu panze negre, doua corabii cu panze albe
                    107 107 102 102 -1 -1 -1
    Challenge 10 - un castel, o corabie cu panze albe, doua cufere
                    105 102 103 103 -1 -1 -1
    */

    int matrice[10][7]; ///vor fi 10 challenge-uri (10 linii) si 7 coloane (un challenge are maxim 7 elemente)
    {
        int x;
        for(x = 1; x <= 7; x++)
            cout << matrice[i][x];
    }

}

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

/* Daniela */
void putImages () {
    /// primul patrat
    readimagefile("resources/1.gif",265,65,335,135); // pirat
    readimagefile("resources/2.gif",335,65,400,135); // corabie
    readimagefile("resources/3.gif",195,135,265,205); // barca
    readimagefile("resources/4.gif",335,135,400,205); // cufar
    readimagefile("resources/5.gif",195,205,265,275); // tentacule

    /// al doilea patrat
    readimagefile("resources/1.gif",425,65,495,135); // pirat
    readimagefile("resources/6.gif",495,65,565,135); // turn
    readimagefile("resources/3.gif",495,135,565,205); // barca
    readimagefile("resources/4.gif",565,135,630,205); // cufar
    readimagefile("resources/5.gif",425,205,495,275); // tentacule
    readimagefile("resources/8.gif",495,205,565,275); // corabie pirati

    /// al treilea patrat
    readimagefile("resources/1.gif",195,295,265,365); // pirat
    readimagefile("resources/2.gif",265,295,335,365); // corabie
    readimagefile("resources/8.gif",335,295,400,365); // corabie pirati
    readimagefile("resources/3.gif",195,365,265,435); // barca
    readimagefile("resources/4.gif",265,365,335,435); // cufar
    readimagefile("resources/8.gif",195,435,265,504); // corabie pirati
    readimagefile("resources/6.gif",265,435,335,504); // turn
    readimagefile("resources/7.gif",335,435,400,504); // piatra

    /// al patrulea patrat
    readimagefile("resources/6.gif",425,365,495,435); // turn
    readimagefile("resources/1.gif",495,365,565,435); // pirat
    readimagefile("resources/7.gif",565,365,630,435); // piatra
    readimagefile("resources/3.gif",425,435,495,504); // barca
    readimagefile("resources/8.gif",495,435,565,504); // corabie pirati
    readimagefile("resources/4.gif",565,435,630,504); // cufar
}
