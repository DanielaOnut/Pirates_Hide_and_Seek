#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

struct piesa {
    int x1, y1, x2, y2;
    char pieceName[40];
} piese[4];
piesa emptyPiece = {-1,-1,-1,-1};

std::string pieceToChar (piesa & piece) {
    std::string pieceName;
    pieceName.append("./../resources/p");
    for (int i = 0; i < 4; ++i)
        if (& piece == & piese[i])
            pieceName.append(strchr(piese[i].pieceName,'p') + 1);
    return pieceName;
}

struct coordonate {
    int x1, y1, x2, y2;
    char element[30];
}vCoord[30];

void initializareCoord () {
    ifstream fin("coordonateImagini.txt");
    for (int i = 0; i < 29; ++i)
        if (i < 25) {
            fin >> vCoord[i].element;
            fin >> vCoord[i].x1 >> vCoord[i].y1 >> vCoord[i].x2 >> vCoord[i].y2;
        }
        else {
            fin >> piese[i % 25].pieceName;
            fin >> piese[i % 25].x1 >> piese[i % 25].y1 >> piese[i % 25].x2 >> piese[i % 25].y2;
        }
    fin.close();
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

    /// desenam imaginile pe ecran si le copiem de pe ecran in memorie
    for (int i = 0; i < 29; ++i)
        if (i < 25) { // alocam si zona de memorie pt a stoca imaginile
            buffer[i] = new char[imagesize(0, 0, 70, 70)];
            readimagefile(vCoord[i].element, vCoord[i].x1, vCoord[i].y1, vCoord[i].x2, vCoord[i].y2);
            getimage (vCoord[i].x1, vCoord[i].y1, vCoord[i].x2, vCoord[i].y2,buffer[i]);
        }
        else {
            buffer[i] = new char[imagesize(0, 0, 110, 110)];
            readimagefile(piese[i % 25].pieceName, piese[i % 25].x1, piese[i % 25].y1, piese[i % 25].x2,piese[i % 25].y2);
            getimage (piese[i % 25].x1, piese[i % 25].y1, piese[i % 25].x2,piese[i % 25].y2,buffer[i]);
        }
}

void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,530);

    setfillstyle(1,COLOR(71,179,192));
    bar(195,65,405,275);
    bar(195,295,405,505);
    bar(425,65,635,275);
    bar(425,295,635,505);

    /// luam imaginile din memorie si le punem pe ecran
    for (int i = 0; i < 29; ++i)
        if (i < 25)
            putimage (vCoord[i].x1, vCoord[i].y1,buffer[i],COPY_PUT);

}

void drawPieces (piesa & movablePiece) {
    // se deseneaza din memorie piesele
    // cu exceptia celei pe care s a dat click
    for (int i = 0; i < 4; ++i)
        if (& movablePiece != & piese[i])
            putimage(piese[i].x1,piese[i].y1,buffer[i + 25],COPY_PUT);
}

void * ch[10];

void play_sound()
{
    PlaySound("hes-a-pirate.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
}

void afisare_challenge(int x) // functia afiseaza dreptunghiul cu challenge-ul din partea dreapta in functie de butonul apasat(x)
{
    ifstream fin("challenge.txt");
    int i = 1 , a = 5, b = 75; // i - index pentru liniile din fisier, a, b - coordonatele care se schimba din 70 in 70 pentru fiecare patrat
    if(x == 6 || x == 8) // pentru challenge-ul 6, 7 si 8 redimensionam pozitiile pentru a fi centrat
    {
        a = 35;
        b = 105;
    }
    else if(x == 7)
    {
        a = 80;
        b = 150;
    }
    char sir[20] = "./../resources/"; // in sir ne vom crea adresa imaginilor din folder-ul resources
    char s[100];
    while(i < x) // parcurgem liniile din fisier si le ignoram pana ajungem la cea de care avem nevoie
    {
        fin.get(s, 100);
        fin.get();
        i++;
    }
    fin.get(s, 100); // in s se afla linia cu challege-ul de care avem nevoie

    char *p = strtok(s, " "); // folosim un strtok pentru a pune in p fiecare imagine (de ex. 101.gif)
    while(p != NULL)
    {
        if(strcmp(p, "-1")!=0) // in fisier avem pun -1 ce reprezinta un patrat care se genereaza gol (ca un fel de spatiu)
        {
            strcat(sir,p);
            readimagefile(sir,0,a,75,b); //punem imaginea la coordonatele corespunzatoare
            setcolor(0); // setam culoarea negru pentru dreptunghiul in care se afla imaginile
            rectangle(0,a,75,b); // desenam dreptunghiul
            //cout << sir << endl;
            a = b;
            b += 70; //marim coordonatele cu 70px (dimensiunea aleasa pentru un patrat)
        }
        else{
            a = b;
            b += 70;
        }
        p = strtok(NULL, " ");
        strcpy(sir, "./../resources/"); // reactualizam sir-ul
    }

}

void updatePage (const char * imagePath, int & page, piesa & piece) {
    setactivepage(page);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();
    drawBoard();
    drawPieces(piece);
//    afisare_challenge(4);
    readimagefile(imagePath,piece.x1,piece.y1,piece.x2,piece.y2);
    setvisualpage(page);
    page++;
}

void rotateImages (int & k, int & page) {
//    if (k % 4 == 0)
//        updatePage("p1r1.gif",page,piece1);
//    else if (k % 4 == 1)
//        updatePage("p1r2.gif",page,piece1);
//    else if (k % 4 == 2)
//        updatePage("p1r3.gif",page,piece1);
//    else if (k % 4 == 3) {
//        page = 0;
//        updatePage("p1r4.gif", page,piece1);
//    }
//    k++;
}

int page = 1;
void movePiece (const char * pieceName, piesa & piece) {
    int x = mousex(), y = mousey();
    if (x - 55 < 75) // daca piesa acopera challenge urile iesi
        return;
    piece.x1 = x - 55; piece.y1 = y - 55;
    piece.x2 = x + 55; piece.y2 = y + 55;

    if (page % 3 == 0)
        page = 1;
    updatePage(pieceName,page,piece);
}

piesa & clickedOnPiece () {
    int x = mousex(), y = mousey();
    for (int i = 0; i < 4; ++i)
        if (x >= piese[i].x1 && x <= piese[i].x2 && y >= piese[i].y1 && y <= piese[i].y2)
            return piese[i];
    return emptyPiece;
}

void waitForMouseClick () { while (!ismouseclick(WM_LBUTTONDOWN)) { delay (100);} }

void mouseEvents () {
    while (1) {
        waitForMouseClick();
        clearmouseclick(WM_LBUTTONDOWN);
        if (ismouseclick(WM_LBUTTONDBLCLK)) {
            cout << "DBLCLK\n";
            clearmouseclick(WM_LBUTTONDBLCLK);
            while (ismouseclick(WM_LBUTTONDBLCLK)) { }
            clearmouseclick(WM_LBUTTONDBLCLK);
            continue;
        }
        piesa & piece = clickedOnPiece();
        if (piece.x1 != -1) { // am dat click pe o piesa
            std::cout << "clickedOnPiece\n";
            std::string pieceName = pieceToChar(piece);
            while (!ismouseclick(WM_LBUTTONUP))
                movePiece(pieceName.c_str(), piece);
            clearmouseclick(WM_LBUTTONUP);

            // modificam imaginea piesei salvata in memorie pentru
            // ca fundalul sa fie transparent
            // extragem numarul piesei
            char name[20]; strcpy (name,pieceName.c_str());
            char * p = strchr(name,'p') + 1; // in p e adresa nr ului piesei
            char * q = strchr(name,'p') + 2;
            * q = 0; // punem null dupa adresa nr ului si salvam in mem
            getimage(piece.x1,piece.y1,piece.x2,piece.y2,buffer[(*p - 49) + 25]);
        }
        else {
            std::cout << "NOTclickedOnPiece\n";
            while (!ismouseclick(WM_LBUTTONUP)) { }
            clearmouseclick(WM_LBUTTONUP);
        }
    }
}

/* Denis */

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
/*
void afisare_challenge(int x) // functia afiseaza dreptunghiul cu challenge-ul din partea dreapta in functie de butonul apasat(x)
{
    int i = 1 , a = 5, b = 75; // i - index pentru liniile din fisier, a, b - coordonatele care se schimba din 70 in 70 pentru fiecare patrat
    if(x == 6 || x == 8) // pentru challenge-ul 6, 7 si 8 redimensionam pozitiile pentru a fi centrat
    {
        a = 35;
        b = 105;
    }
    else if(x == 7)
    {
        a = 80;
        b = 150;
    }
    char sir[20] = "./../resources/"; // in sir ne vom crea adresa imaginilor din folder-ul resources
    char s[100];
    while(i < x) // parcurgem liniile din fisier si le ignoram pana ajungem la cea de care avem nevoie
    {
        fin.get(s, 100);
        fin.get();
        i++;
    }
    fin.get(s, 100); // in s se afla linia cu challege-ul de care avem nevoie

    char *p = strtok(s, " "); // folosim un strtok pentru a pune in p fiecare imagine (de ex. 101.gif)
    while(p != NULL)
    {
        if(strcmp(p, "-1")!=0) // in fisier avem pun -1 ce reprezinta un patrat care se genereaza gol (ca un fel de spatiu)
        {
            strcat(sir,p);
            readimagefile(sir,0,a,75,b); //punem imaginea la coordonatele corespunzatoare
            setcolor(0); // setam culoarea negru pentru dreptunghiul in care se afla imaginile
            rectangle(0,a,75,b); // desenam dreptunghiul
            //cout << sir << endl;
            a = b;
            b += 70; //marim coordonatele cu 70px (dimensiunea aleasa pentru un patrat)
        }
        else{
            a = b;
            b += 70;
        }
        p = strtok(NULL, " ");
        strcpy(sir, "./../resources/"); // reactualizam sir-ul
    }

}
*/
/*
struct patrat{
    int x1, y1, x2, y2;
}v[5];

v[1].x1 = v[2].x1 = 195;
v[1].y1 = v[3].y1 = 65;
v[1].x2 = v[2].x2 = 405;
v[1].y2 = v[3].y2 = 275;
v[2].y1 = v[4].y1 = 295;
v[2].y2 = v[4].y2 = 505;
v[3].x1 = v[4].x1 = 425;
v[3].x2 = v[4].x2 = 635;

bar(195,65,405,275);
bar(195,295,405,505);
bar(425,65,635,275);
bar(425,295,635,505);

*/
