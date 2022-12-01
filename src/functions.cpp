#include <iostream>
#include <winbgim.h>

struct piesa {
    int x1, y1, x2, y2;
}; // initializarea pozitiilor pieselor
piesa piece1 = {720,50,830,160};
piesa piece2 = {720,170,830,280};
piesa piece3 = {720,290,830,400};
piesa piece4 = {720,410,830,520};
piesa emptyPiece = {-1,-1,-1,-1};

const char * pieceToChar (piesa & piece) {
    std::string pieceName;
    if (& piece == & piece1)
        pieceName.append("p1r1.gif");
    else if (& piece == & piece2)
        pieceName.append("p2r1.gif");
    else if (& piece == & piece3)
        pieceName.append("p3r1.gif");
    else if (& piece == & piece4)
        pieceName.append("p4r1.gif");
    return pieceName.c_str();
}

void * buffer[30];
void initialDrawing () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,530);

    setfillstyle(1,COLOR(71,179,192));
    bar(195,65,405,275);
    bar(195,295,405,505);
    bar(425,65,635,275);
    bar(425,295,635,505);

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
    readimagefile("./../resources/100.gif",495,365,565,435); // pirat
    readimagefile("./../resources/106.gif",565,365,630,435); // piatra
    readimagefile("./../resources/102.gif",425,435,495,504); // barca
    readimagefile("./../resources/107.gif",495,435,565,504); // corabie pirati
    readimagefile("./../resources/103.gif",565,435,630,504); // cufar

    /// desenarea initiala a pieselor
    readimagefile("./../resources/p1r1.gif",piece1.x1,piece1.y1,piece1.x2,piece1.y2);
    readimagefile("./../resources/p2r1.gif",piece2.x1,piece2.y1,piece2.x2,piece2.y2);
    readimagefile("./../resources/p3r1.gif",piece3.x1,piece3.y1,piece3.x2,piece3.y2);
    readimagefile("./../resources/p4r1.gif",piece4.x1,piece4.y1,piece4.x2,piece4.y2);


    /// se pun toate imaginile de pe ecran in memorie
    for (int i = 0; i < 30; ++i) // am alocat zona de memorie
        if (i < 25)
            buffer[i] = new char[imagesize(0, 0, 70, 70)];
        else
            buffer[i] = new char[imagesize(0, 0, 110, 110)];
    /// primul patrat
    getimage (265,65,335,135,buffer[0]);
    getimage (335,65,400,135,buffer[1]);
    getimage (195,135,265,205,buffer[2]);
    getimage (335,135,400,205,buffer[3]);
    getimage (195,205,265,275,buffer[4]);

    /// al doilea patrat
    getimage(425,65,495,135,buffer[5]);
    getimage(495,65,565,135,buffer[6]); // turn
    getimage(495,135,565,205,buffer[7]); // barca
    getimage(565,135,630,205,buffer[8]); // cufar
    getimage(425,205,495,275,buffer[9]); // tentacule
    getimage(495,205,565,275,buffer[10]); // corabie pirati

    /// al treilea patrat
    getimage(195,295,265,365,buffer[11]); // pirat
    getimage(265,295,335,365,buffer[12]); // corabie
    getimage(335,295,400,365,buffer[13]); // corabie pirati
    getimage(195,365,265,435,buffer[14]); // barca
    getimage(265,365,335,435,buffer[15]); // cufar
    getimage(195,435,265,504,buffer[16]); // corabie pirati
    getimage(265,435,335,504,buffer[17]); // turn
    getimage(335,435,400,504,buffer[18]); // piatra

    /// al patrulea patrat
    getimage(425,365,495,435,buffer[19]); // turn
    getimage(495,365,565,435,buffer[20]); // pirat
    getimage(565,365,630,435,buffer[21]); // piatra
    getimage(425,435,495,504,buffer[22]); // barca
    getimage(495,435,565,504,buffer[23]); // corabie pirati
    getimage(565,435,630,504,buffer[24]); // cufar

    getimage (piece1.x1,piece1.y1,piece1.x2,piece1.y2,buffer[25]);
    getimage (piece2.x1,piece2.y1,piece2.x2,piece2.y2,buffer[26]);
    getimage (piece3.x1,piece3.y1,piece3.x2,piece3.y2,buffer[27]);
    getimage (piece4.x1,piece4.y1,piece4.x2,piece4.y2,buffer[28]);
}

void putImages () {
    ///luam imaginile salvate in memorie si le afisam pe ecran
    /// primul patrat
    putimage(265, 65 ,buffer[0],COPY_PUT); // pirat
    putimage(335, 65 ,buffer[1],COPY_PUT); // corabie
    putimage(195, 135,buffer[2],COPY_PUT); // barca
    putimage(335, 135,buffer[3],COPY_PUT); // cufarbuffer[],COPY_PUT
    putimage(195, 205,buffer[4],COPY_PUT); // tentacule

    /// al doilea patrat
    putimage(425, 65 ,buffer[5],COPY_PUT); // pirat
    putimage(495, 65 ,buffer[6],COPY_PUT); // turn
    putimage(495, 135,buffer[7],COPY_PUT); // barca
    putimage(565, 135,buffer[8],COPY_PUT); // cufar
    putimage(425, 205,buffer[9],COPY_PUT); // tentacule
    putimage(495, 205,buffer[10],COPY_PUT); // corabie pirati

    /// al treilea patrat
    putimage(195, 295,buffer[11],COPY_PUT); // pirat
    putimage(265, 295,buffer[12],COPY_PUT); // corabie
    putimage(335, 295,buffer[13],COPY_PUT); // corabie pirati
    putimage(195, 365,buffer[14],COPY_PUT); // barca
    putimage(265, 365,buffer[15],COPY_PUT); // cufar
    putimage(195, 435,buffer[16],COPY_PUT); // corabie pirati
    putimage(265, 435,buffer[17],COPY_PUT); // turn
    putimage(335, 435,buffer[18],COPY_PUT); // piatra

    /// al patrulea patrat
    putimage(425, 365,buffer[19],COPY_PUT); // turn
    putimage(495, 365,buffer[20],COPY_PUT); // pirat
    putimage(565, 365,buffer[21],COPY_PUT); // piatra
    putimage(425, 435,buffer[22],COPY_PUT); // barca
    putimage(495, 435,buffer[23],COPY_PUT); // corabie pirati
    putimage(565, 435,buffer[24],COPY_PUT); // cufar
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

void drawPieces (piesa & movablePiece) {
    // se deseneaza din memorie piesele
    // cu exceptia celei pe care s a dat click
    if (& movablePiece == & piece1) {
        putimage(piece2.x1, piece2.y1, buffer[26], COPY_PUT);
        putimage(piece3.x1, piece3.y1, buffer[27], COPY_PUT);
        putimage(piece4.x1, piece4.y1, buffer[28], COPY_PUT);
    }
    else if (& movablePiece == & piece2) {
        putimage(piece1.x1, piece1.y1, buffer[25], COPY_PUT);
        putimage(piece3.x1, piece3.y1, buffer[27], COPY_PUT);
        putimage(piece4.x1, piece4.y1, buffer[28], COPY_PUT);
    }
    else if (& movablePiece == & piece3) {
        putimage(piece1.x1, piece1.y1, buffer[25], COPY_PUT);
        putimage(piece2.x1, piece2.y1, buffer[26], COPY_PUT);
        putimage(piece4.x1, piece4.y1, buffer[28], COPY_PUT);
    }
    else if (& movablePiece == & piece4) {
        putimage(piece1.x1, piece1.y1, buffer[25], COPY_PUT);
        putimage(piece2.x1, piece2.y1, buffer[26], COPY_PUT);
        putimage(piece3.x1, piece3.y1, buffer[27], COPY_PUT);
    }
}

void updatePage (const char * image, int & page, piesa & piece) {
    setactivepage(page);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();
    drawBoard();
    drawPieces(piece);
    std::string path = "./../resources/";
    path.append(image);
    readimagefile(path.c_str(),piece.x1,piece.y1,piece.x2,piece.y2);
    setvisualpage(page);
    page++;
}

void rotateImages (int & k, int & page) {
    if (k % 4 == 0)
        updatePage("p1r1.gif",page,piece1);
    else if (k % 4 == 1)
        updatePage("p1r2.gif",page,piece1);
    else if (k % 4 == 2)
        updatePage("p1r3.gif",page,piece1);
    else if (k % 4 == 3) {
        page = 0;
        updatePage("p1r4.gif", page,piece1);
    }
    k++;
}

int page = 1;
void movePiece (const char * pieceName, piesa & piece) {
    int x = mousex(), y = mousey();
    piece.x1 = x - 55; piece.y1 = y - 55;
    piece.x2 = x + 55; piece.y2 = y + 55;

    if (page % 3 == 0)
        page = 1;
    updatePage(pieceName,page,piece);
}

piesa & clickedOnPiece () {
    int x = mousex(), y = mousey();
    if (x >= piece1.x1 && x <= piece1.x2 && y >= piece1.y1 && y <= piece1.y2)
        return piece1;
    else if (x >= piece2.x1 && x <= piece2.x2 && y >= piece2.y1 && y <= piece2.y2)
        return piece2;
    else if (x >= piece3.x1 && x <= piece3.x2 && y >= piece3.y1 && y <= piece3.y2)
        return piece3;
    else if (x >= piece4.x1 && x <= piece4.x2 && y >= piece4.y1 && y <= piece4.y2)
        return piece4;
    return emptyPiece;
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
