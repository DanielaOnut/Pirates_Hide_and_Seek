#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

/* Denis */
int mat_tabla[7][7];

/* Daniela */
struct piesa {
    int x1, y1, x2, y2;
    char pieceName[40];
    int rotatie = 1; /// de la 1 - 4
    int mat[3][3];
} piese[4];
piesa emptyPiece = {-1,-1,-1,-1};

struct patrat {
    int x1, y1, x2, y2;
    piesa * piesa = & emptyPiece; // retinem ce piesa e in fiecare patrat
} patrate[4];

struct coordonate {
    int x1, y1;
    char element[30];
}vCoord[37];

/* Denis */

void * buffer[45]; // 45 - sunt 36 de imagini in total, dar alocam 45 sa fie loc + piesele pe langa cele 36
void desenare_initiala()
{
    ifstream fin("matrice_tabla.txt");
    setfillstyle(1,COLOR(84,197,210));
    bar(170,40,660,530);
    char sursa[30] = "./../resources/";
    char gif[5] = ".gif";
    char numar[4];
    int i, j, p = 125, q = 5, lg = 0;

    for(i = 1; i <= 6; i++)
        for(j = 1; j <= 6; j++)
            fin >> mat_tabla[i][j];
    int x = 195, y = 65, z = 635, t = 505;
    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= 6; j++)
        {
            numar[0] = char(mat_tabla[i][j] /100) + 48;
            numar[1] = char(mat_tabla[i][j] /10 % 10) +48;
            numar[2] = char(mat_tabla[i][j] % 10) + 48;
            numar[3] = '\0';
//            cout << numar << endl;
            strcat(sursa,numar);
            strcat(sursa,gif);
            if(i > 3 && j > 3)
            {
                buffer[lg] = new char[imagesize(0,0,70,70)];
                readimagefile(sursa, j*70 + 20 + p,i*70 + 20 - q,j*70 + 70 + 20 + p,i*70 + 70 + 20 - q);
                getimage(j*70 + 20 + p,i*70 + 20 - q,j*70 + 70 + 20 + p,i*70 + 70 + 20 - q, buffer[lg]);
                vCoord[lg].x1 = j * 70 + 20 + p;
                vCoord[lg].y1 = i * 70 + 20 - q;
                strcpy(vCoord[lg].element,sursa);
                lg++;
            }
            else if(i <= 3 && j > 3)
            {
                buffer[lg] = new char[imagesize(0,0,70,70)];
                readimagefile(sursa, j*70 + 20 + p,i*70 - q,j*70 + 70 + 20 + p,i*70 + 70 - q);
                getimage(j*70 + 20 + p,i*70 - q,j*70 + 70 + 20 + p,i*70 + 70 - q, buffer[lg]);
                vCoord[lg].x1 = j*70 + 20 + p;
                vCoord[lg].y1 = i*70 - q;
                strcpy(vCoord[lg].element,sursa);
                lg++;
            }
                    else if(i > 3 && j <= 3)
                    {
                        buffer[lg] = new char[imagesize(0,0,70,70)];
                        readimagefile(sursa, j*70 + p,i*70 + 20 - q,j*70 + 70 + p,i*70 + 70 + 20 - q);
                        getimage(j*70 + p,i*70 + 20 - q,j*70 + 70 + p,i*70 + 70 + 20 - q, buffer[lg]);
                        vCoord[lg].x1 = j*70 + p;
                        vCoord[lg].y1 = i*70 + 20 - q;
                        strcpy(vCoord[lg].element,sursa);
                        lg++;
                    }
                        else if(i <= 3 && j <= 3)
                        {
                            buffer[lg] = new char[imagesize(0,0,70,70)];
                            readimagefile(sursa, j*70 + p,i*70 - q,j*70 + 70 + p,i*70 + 70 - q);
                            getimage(j*70 + p,i*70 - q,j*70 + 70 + p,i*70 + 70 - q, buffer[lg]);
                            vCoord[lg].x1 = j*70 + p;
                            vCoord[lg].y1 = i*70 - q;
                            strcpy(vCoord[lg].element,sursa);
                            lg++;
                        }
            //cout << sursa << endl;
            strcpy(sursa, "./../resources/");
        }
    }
    ifstream finn("coordonateImagini.txt");
    for(int w = 0; w < 4; w++)
    {
        finn >> piese[w].pieceName;
        finn >> piese[w].x1 >> piese[w].y1 >> piese[w].x2 >> piese[w].y2;
        buffer[lg] = new char[imagesize(0,0,110,110)];
        readimagefile(piese[w].pieceName,piese[w].x1, piese[w].y1, piese[w].x2,piese[w].y2);
        getimage(piese[w].x1, piese[w].y1, piese[w].x2,piese[w].y2, buffer[lg++]);
        //cout << piese[w].pieceName << piese[w].x1 << piese[w].y1 << piese[w].x2 << piese[w].y2 << endl;
    }

}

/* Daniela */

void initializareCoord () {
    // salvam coordonatele patratelor tablei
    patrate[0] = {195,65,405,275};
    patrate[1] = {425,65,635,275};
    patrate[2] = {195,295,405,505};
    patrate[3] = {425,295,635,505};

}

void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,530);

    /// luam imaginile din memorie si le punem pe ecran
    for (int i = 0; i < 36; ++i)
        putimage(vCoord[i].x1, vCoord[i].y1, buffer[i], COPY_PUT);
}

void drawPieces (piesa & movablePiece) {
    // se deseneaza din memorie piesele
    // cu exceptia celei pe care s a dat click
    for (int i = 0; i < 4; ++i)
        if (& movablePiece != & piese[i])
            putimage(piese[i].x1,piese[i].y1,buffer[i + 36],COPY_PUT);
}

/* Denis */
void * vector_imagine[10];

void play_sound()
{
//    PlaySound("hes-a-pirate.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
}

int cont;
void afisare_challenge(int x, int y) // functia afiseaza dreptunghiul cu challenge-ul din partea dreapta in functie de butonul apasat(x)
{
    ifstream fin("challenge.txt");
    if(y == 1)cont = 0;
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
            if(y == 0)
            {
                vector_imagine[cont] = new char[imagesize(0,0,75,75)];
                readimagefile(sir,0,a,75,b); //punem imaginea la coordonatele corespunzatoare
                getimage(0,a,75,b,vector_imagine[cont]);
                cont++;
            }
            else if(y == 1)
                {
                    putimage(0,a,vector_imagine[cont], COPY_PUT);
                    cont++;
                }

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
    afisare_challenge(1, 1);
    readimagefile(imagePath,piece.x1,piece.y1,piece.x2,piece.y2);
    setvisualpage(page);
    page++;
}

void rotateImages(piesa &piece)
{
    piece.rotatie++;
    if(piece.rotatie % 5 == 0)piece.rotatie = 1;
    cout << piece.pieceName << '\n';
    char cifra[2];
    cifra[0] = char(piece.rotatie + 48);
    cifra[1] = '\0';
    strcpy(piece.pieceName + 18, cifra);
    strcpy(piece.pieceName + 19, ".gif");
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
    //cout << "merge si aici\n";
    updatePage(pieceName,page,piece);
}

piesa & clickedOnPiece () {
    int x = mousex(), y = mousey();
    for (int i = 0; i < 4; ++i)
        if (x >= piese[i].x1 && x <= piese[i].x2 && y >= piese[i].y1 && y <= piese[i].y2)
            return piese[i];
    return emptyPiece;
}

bool isPieceInSquare (piesa & piece) {
    int index = -1; // verificam daca piesa curenta e deja intr un patrat
    for (int i = 0; i < 4; ++i) {
        if (patrate[i].piesa == & piece)
                index = i; // retinem patratul in care este piesa

    }
    // aflam coordonatele centrului piesei (piesa e 110x110)
    int x = piece.x1 + 55, y = piece.y1 + 55;
    for (int i = 0; i < 4; ++i)
        if (x >= patrate[i].x1 && y >= patrate[i].y1
            && x <= patrate[i].x2 && y <= patrate[i].y2) {
            if (patrate[i].piesa != & emptyPiece && index != -1) { // daca in patrat e deja o piesa
                cout << "patrat ocupat\n";
                if(patrate[i].piesa == patrate[index].piesa){
                        cout << "aceeasi piesa\n";
                        rotateImages(piece);
                }

                patrat aux = patrate[i];
                patrate[i].piesa->x1 = patrate[index].x1;
                patrate[i].piesa->y1 = patrate[index].y1;
                patrate[i].piesa->x2 = patrate[index].x2;
                patrate[i].piesa->y2 = patrate[index].y2;

                patrate[index].piesa->x1 = aux.x1;
                patrate[index].piesa->y1 = aux.y1;
                patrate[index].piesa->x2 = aux.x2;
                patrate[index].piesa->y2 = aux.y2;
                swap (patrate[i].piesa,patrate[index].piesa);
                // am interschimbat piesele pe tabla
                return true;

            }
            if (index != -1) patrate[index].piesa = & emptyPiece;
            piece.x1 = patrate[i].x1; piece.y1 = patrate[i].y1;
            piece.x2 = patrate[i].x2; piece.y2 = patrate[i].y2;
            patrate[i].piesa = & piece;
            return true;
        }
//    std::cout << index + 1 << '\n';
    patrate[index].piesa = & emptyPiece;
    return false;
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
            while (!ismouseclick(WM_LBUTTONUP))
                movePiece(piece.pieceName, piece);
            clearmouseclick(WM_LBUTTONUP);

            if (isPieceInSquare(piece)) {
               std::cout << "inSquare\n";
                if (page % 3 == 0)
                    page = 1;
                updatePage(piece.pieceName,page,piece);
            }

            //for(int i = 0; i < 4; i++)
                //verificare castigator

            // modificam imaginea piesei salvata in memorie pentru
            // ca fundalul sa fie transparent
            // extragem numarul piesei
            char name[20]; strcpy (name,piece.pieceName);
            char * p = strchr(name,'p') + 1; // in p e adresa nr ului piesei
            char * q = strchr(name,'p') + 2;
            * q = 0; // punem null dupa adresa nr ului si salvam in mem
            buffer[(*p - 49) + 36] = new char [imagesize(0,0,210,210)];
            getimage(piece.x1,piece.y1,piece.x2,piece.y2,buffer[(*p - 49) + 36]);
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
