#include <iostream>
#include <winbgim.h>

void putImages () {
    /// primul patrat
    readimagefile("./../resources/100.gif",265,65,335,135); // pirat
    readimagefile("./../resources/101.gif",335,65,400,135); // corabie
    readimagefile("./../resources/102.gif",195,135,265,205); // barca
    readimagefile("./../resources/103.gif",335,135,400,205); // cufar
    readimagefile("./../resources/104.gif",195,205,265,275); // tentacule

    /// al doilea patrat
    readimagefile("./../resources/100.gif",425,65,495,135); // pirat
    readimagefile("./../resources/105.gif",495,65,565,135); // turn
    readimagefile("./../resources/102.gif",495,135,565,205); // barca
    readimagefile("./../resources/103.gif",565,135,630,205); // cufar
    readimagefile("./../resources/104.gif",425,205,495,275); // tentacule
    readimagefile("./../resources/107.gif",495,205,565,275); // corabie pirati

    /// al treilea patrat
    readimagefile("./../resources/100.gif",195,295,265,365); // pirat
    readimagefile("./../resources/101.gif",265,295,335,365); // corabie
    readimagefile("./../resources/107.gif",335,295,400,365); // corabie pirati
    readimagefile("./../resources/102.gif",195,365,265,435); // barca
    readimagefile("./../resources/103.gif",265,365,335,435); // cufar
    readimagefile("./../resources/107.gif",195,435,265,504); // corabie pirati
    readimagefile("./../resources/105.gif",265,435,335,504); // turn
    readimagefile("./../resources/106.gif",335,435,400,504); // piatra

    /// al patrulea patrat
    readimagefile("./../resources/105.gif",425,365,495,435); // turn
    readimagefile("./../resources/re",495,365,565,435); // pirat
    readimagefile("./../resources/106.gif",565,365,630,435); // piatra
    readimagefile("./../resources/102.gif",425,435,495,504); // barca
    readimagefile("./../resources/107.gif",495,435,565,504); // corabie pirati
    readimagefile("./../resources/103.gif",565,435,630,504); // cufar
}


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

void rotateImages () {
    int k = 0;
    while(getch()) {
        if (k % 4 == 0) {
            cleardevice();
            drawBoard();
            readimagefile("./../resources/p1r1.gif",195,65,405,275);
        }
        if (k % 4 == 1) {
            cleardevice();
            drawBoard();
            readimagefile("./../resources/p1r2.gif",195,65,405,275);
        }
        if (k % 4 == 2) {
            cleardevice();
            drawBoard();
            readimagefile("./../resources/p1r3.gif",195,65,405,275);
        }
        if (k % 4 == 3) {
            cleardevice();
            drawBoard();
            readimagefile("./../resources/p1r4.gif",195,65,405,275);
        }
        k++;
    }
}

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
            std::cout << matrice[i][x];
    }

}
