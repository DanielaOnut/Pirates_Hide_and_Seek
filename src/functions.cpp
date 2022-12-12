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
    ifstream fin("matrice_tabla.txt"); // iau elementele din fisier
    setfillstyle(1,COLOR(84,197,210));
    bar(170,40,660,530); // creez patratul mare
    char sursa[30] = "./../resources/";
    char gif[5] = ".gif";
    char numar[4];
    int i, j, p = 125, q = 5, lg = 0;

    for(i = 1; i <= 6; i++)
        for(j = 1; j <= 6; j++)
            fin >> mat_tabla[i][j]; // imi construiesc matricea care continele toate elementele de pe tabla
    int x = 195, y = 65, z = 635, t = 505;
    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= 6; j++)
        {
            //in numar voi crea nr elementului (care e de 3 cifre, ex: 108)
            numar[0] = char(mat_tabla[i][j] /100) + 48;
            numar[1] = char(mat_tabla[i][j] /10 % 10) +48;
            numar[2] = char(mat_tabla[i][j] % 10) + 48;
            numar[3] = '\0';
//            cout << numar << endl;
            strcat(sursa,numar);
            strcat(sursa,gif); //creez sursa elementului
            ///Am 4 cazuri deoarece impart tabla in 4 patrate, iar intre patrate se afla o distanta de 20px; Totodata, in p si q sunt nr de px ca tabla sa fie incadrata perfect in patratul mare
            if(i > 3 && j > 3)
            {
                ///Pentru fiecare imagine aloc memorie in buffer, citesc imaginea si o salvez in memorie impreuna cu coordonatele sale
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
            strcpy(sursa, "./../resources/"); //resetez in sursa path-ul corect, pe parcurs el se alterneaza
        }
    }
    ifstream finn("coordonateImagini.txt"); //de aici iau piesele impreuna cu coordonatele lor si le salvez tot in buffer
    for (int w = 0; w < 4; w++)
    {
        finn >> piese[w].pieceName;
        finn >> piese[w].x1 >> piese[w].y1 >> piese[w].x2 >> piese[w].y2;
        buffer[lg] = new char[imagesize(0,0,110,110)];
        readimagefile(piese[w].pieceName,piese[w].x1, piese[w].y1, piese[w].x2,piese[w].y2);
        getimage(piese[w].x1, piese[w].y1, piese[w].x2,piese[w].y2, buffer[lg++]);
        //cout << piese[w].pieceName << piese[w].x1 << piese[w].y1 << piese[w].x2 << piese[w].y2 << endl;
    }

}

int nrPiesa(piesa &piece) //obtin numarul piesei extragand din nume nr ei
{
    char name[35]; strcpy (name,piece.pieceName);
    char * p = strchr(name,'p') + 1; // in p e adresa nr ului piesei
    char * q = strchr(name,'p') + 2;
    * q = 0;
    return atoi(p);
    //cout << p << endl;
}

void matrici_piese() //completez matricile fiecare piese in functie de rotirea pe care o are
{
    int i, index, val, j, k;
    for(k = 0; k < 4; k++) // de la 0 la 3 pentru ca sunt 4 piese in total
    {
        int numar = nrPiesa(piese[k]);
        char nume_fisier[15];
        nume_fisier[0] = 'p';
        nume_fisier[1] = char(k + 1 + 48); ///In nume_fisier imi creez path-ul fisierului pe care  vreau sa-l deschid (sunt 4 fisiere, cate 1 per piesa)
        strcpy(nume_fisier + 2, ".txt");
        ifstream fin(nume_fisier);
        index = 9 * (piese[k].rotatie - 1) + 1; // formula e 9 * ... pentru ca matricile sunt de 3 pe 3 si eu vreau sa stiu cate elemente trebuie sa sar
        for(i = 1; i < index; i++)
            fin >> val; // sar elementele care nu ma intereseaza (care nu au rotatia potrivita)
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                fin >> piese[k].mat[i][j]; //pun in mat din struct matricea corespunzatoare
    }
}


bool verificare_solutie(int x) // x va fi challenge-ul
{
    ifstream fin("solutii_challenge.txt");
    int vect_solutii_challenge[9], vect_elemente_tabla[9]; //sunt cei 2 vectori de frecventa, unul corespunzator a ce se afla pe tabla, unul la ce ar trebui sa se afle pentru a castiga
    int ct;
    for(ct = 0; ct < 8; ct++) //de fiecare data reintializez toate comp. din vectori cu 0 pentru ca functia se aplica pentru fiecare incercare
    {
        vect_solutii_challenge[ct] = 0;
        vect_elemente_tabla[ct] = 0;
    }

    int matrice_solutie[7][7]; ///Mai jos imi creez matricea mare a tablei conform matricilor micute din struct
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            matrice_solutie[i][j] = patrate[0].piesa -> mat[i][j];
    for(i = 0; i < 3; i++)
        for(j = 3; j < 6; j++)
            matrice_solutie[i][j] = patrate[1].piesa -> mat[i][j-3];
    for(i = 3; i < 6; i++)
        for(j = 0; j < 3; j++)
            matrice_solutie[i][j] = patrate[2].piesa -> mat[i-3][j];
    for(i = 3; i < 6; i++)
        for(j = 3; j < 6; j++)
            matrice_solutie[i][j] = patrate[3].piesa -> mat[i-3][j-3];

    int matrice_finala_solutie[7][7]; ///In matrice finala inmultesc tot ce se afla pe tabla cu matricea construita anterior, si o sa dea 0 acl unde exista piese
    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            matrice_finala_solutie[i][j] = mat_tabla[i+1][j+1] * matrice_solutie[i][j]; //mat_tabla are i+1 si j+1 deoarece aceasta matrice a fost indexata de la 1, pe cand restul matricilor folosite de la 0

    int y = 1, val;
    char s[100];
    while(y < x) ///Aici preiau din fisier solutia care ar trebui sa fie corecta pentru fiecare challenge (sar liniile care nu imi trebuie pana ajung la challenge-ul de care am nevoie)
    {
        fin.get(s, 100);
        fin.get();
        y++;
    }
    fin.get(s, 100); //In s am challenge-ul curent
    char * p = strtok(s, " "); ///Sparg in cuvinte s-ul care va fi reprezentat de fiecare element din challenge
    while(p != NULL)
    {
        val = atoi(p); //transform din char in int
        vect_solutii_challenge[val-100]++; //val-100 pentru ca vectorii sunt de la 0 la 7, iar imaginile de la 100 la 107
        p = strtok(NULL, " ");
    }

    for(i = 0; i < 6; i++)
        for(j = 0; j < 6; j++)
            if(matrice_finala_solutie[i][j] != 0)
                vect_elemente_tabla[matrice_finala_solutie[i][j] - 100]++; //aici pun in vectorul ce contine el. de pe tabla elementele din matricea construita diferite de 0 (elementele care sunt vizibile pe tabla)

    /*
    ///Afisare vectori de frecventa (pentru verificare)
    for(i = 0; i < 8; i++)
        cout << vect_elemente_tabla[i] << " ";
    cout << endl;
    for(i = 0; i < 8; i++)
        cout << vect_solutii_challenge[i] << " ";
    cout << endl;
    */

    for(i = 0; i < 8; i++)
        if(vect_elemente_tabla[i] != vect_solutii_challenge[i])return false; //compar cei doi vectori de frecventa si trag concluzia
    return true;
}

int page = 1;
void castigare_challenge()
{
    setactivepage(13);
    cleardevice();
    readimagefile("./../resources/congrats.gif",160,50,800,590);
    cout << "a mers";
    setvisualpage(13);
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

void * img_finish;

void btn_finish(int x)
{
    if(x == 0)
    {
    img_finish = new char[imagesize(0, 0, 265, 114)];
    readimagefile("./../resources/buton_finish.gif", 370, 540, 470, 580);
    getimage(370, 540, 470, 580, img_finish);
    }
    else putimage(370, 540, img_finish, COPY_PUT);
}

void updatePage (int & page, piesa & piece) {
    setactivepage(page);
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();
    drawBoard();
    drawPieces(piece);
    afisare_challenge(3, 1);
    btn_finish(1);
    readimagefile(piece.pieceName,piece.x1,piece.y1,piece.x2,piece.y2);
    setvisualpage(page);
    page++;
}

void rotateImages(piesa &piece)
{
    piece.rotatie++;
    if (piece.rotatie % 5 == 0) piece.rotatie = 1;
    char cifra[2];
    cifra[0] = char(piece.rotatie + 48);
    cifra[1] = '\0';
    strcpy(piece.pieceName + 18, cifra);
    strcpy(piece.pieceName + 19, ".gif");
}

void movePiece (piesa & piece) {
    int x = mousex(), y = mousey();
    if (x - 55 < 75) // daca piesa acopera challenge urile iesi
        return;
    piece.x1 = x - 55; piece.y1 = y - 55;
    piece.x2 = x + 55; piece.y2 = y + 55;

    if (page % 3 == 0)
        page = 1;
    updatePage(page,piece);
}

bool clickonFinish()
{
    int x = mousex(), y = mousey();
    if(x >= 370 && x <= 540 && y >= 470 && y <= 580)return true;
    return false;
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
                    piece.x1 = patrate[i].x1; piece.y1 = patrate[i].y1;
                    piece.x2 = patrate[i].x2; piece.y2 = patrate[i].y2;
                    rotateImages(piece);
                    return true;
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

void waitForMouseClick () { while (!ismouseclick(WM_LBUTTONDBLCLK) && !ismouseclick(WM_LBUTTONDOWN)
&& !ismouseclick(WM_RBUTTONDOWN)) { delay (100);} }

void mouseEvents () {
    bool pieceRotated;
    while (1) {
        pieceRotated = false;
        waitForMouseClick();
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_LBUTTONDOWN);
        if (ismouseclick(WM_RBUTTONDOWN)) {
            cout << "RCLICK\n";
            pieceRotated = true;
        }
        piesa & piece = clickedOnPiece();
        if (& piece != & emptyPiece) { // am dat click pe o piesa
            std::cout << "clickedOnPiece\n";
            while (!ismouseclick(WM_LBUTTONUP) && !pieceRotated)
                movePiece(piece);
            clearmouseclick(WM_LBUTTONUP);
            clearmouseclick(WM_RBUTTONDOWN);

            if (isPieceInSquare(piece)) {
                if (page % 3 == 0)
                    page = 1;
                updatePage(page,piece);
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
            if(clickonFinish() == 1)
            {
            matrici_piese();
             if(verificare_solutie(3) == 1)
                {
                    cout << "CHALLENGE CASTIGAT" << endl;
                    castigare_challenge();
                }
            else cout << "MAI INCEARCA" << endl;

            }
            if (ismouseclick(WM_RBUTTONDOWN)) {
                clearmouseclick(WM_RBUTTONDOWN);
                continue;
            }
            while (!ismouseclick(WM_LBUTTONUP)) { }
            clearmouseclick(WM_LBUTTONUP);
        }
    }
}
