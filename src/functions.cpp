#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include <ctime>
#include <cstdlib> // current date and time
using namespace std;

/* Denis */
int mat_tabla[7][7];
ofstream fout("rezultate.txt", ios::app); //ios:app - optiune pentru a nu rescrie fisierul, ci a scrie in continuarea continutului existent
int rt = 0; //contor buton hint

/* Daniela */
int challengeNo = 0;
int unit = 1;
clock_t startTime;

/* Daniela */

struct piesa {
    int x1, y1, x2, y2;
    char pieceName[40];
    int rotatie = 1; /// de la 1 - 4
    int mat[3][3];
} piese[4];
piesa emptyPiece = {-1,-1,-1,-1};

/* Daniela */

struct patrat {
    int x1, y1, x2, y2;
    piesa * piesa = & emptyPiece; // retinem ce piesa e in fiecare patrat
} patrate[4];

/* Daniela */

struct coordonate {
    int x1, y1;
    char element[30];
}vCoord[37];

/* Daniela */

std::string timeToString () {
    char string[8];
    clock_t currentTime = clock();
    int s = (currentTime - startTime) / 1000;
    int mins = (currentTime - startTime) / 60000;
    int hrs = (currentTime - startTime) / 3600000;

    if (hrs >= 0) strcpy(string,"0"), itoa (hrs,string + 1,10), strcat(string,":");
    else strcpy (string,"00:");
    if (mins >= 0) {
        if (mins >= 60) mins -= 60 * hrs;
        if (mins < 10)
            strcat (string,"0"), itoa (mins,string + 1, 10);
        else itoa (mins,string,10);
        strcat(string,":");
    }
    if (s >= 0) {
        if (s >= 60) s -= 60 * mins;
        if (s < 10)
            strcat (string,"0"), itoa (s,string + 4, 10);
        else
            itoa (s,string + 3,10);
    }
    return string;
}

/* Daniela */

void drawTimer () {
    char sir[8];
    strcpy(sir,timeToString().c_str());

    setbkcolor(COLOR(206, 197, 189));
    setcolor(BLACK);
    settextstyle(8, HORIZ_DIR,4);
    outtextxy(370,7,sir);
}

/* Denis */

void * buffer[45]; // 45 - sunt 36 de imagini in total, dar alocam 45 sa fie loc + piesele pe langa cele 36
void desenare_initiala()
{
    ///Adaugam background in memorie
    buffer[42] = new char[imagesize(0, 0, 900, 590)];
    readimagefile("./../resources/backgroundtest.jpg",0, 0, 900, 590);
    getimage(0,0,900,590,buffer[42]);

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
    drawTimer();
}

/* Denis si Daniela */

int nrPiesa(piesa &piece) //obtin numarul piesei extragand din nume nr ei
{
    char name[35]; strcpy (name,piece.pieceName);
    char * p = strchr(name,'p') + 1; // in p e adresa nr ului piesei
    char * q = strchr(name,'p') + 2;
    * q = 0;
    return atoi(p);
    //cout << p << endl;
}

/* Denis */

void matrici_piese() //completez matricile fiecare piese in functie de rotirea pe care o are
{
    int i, index, val, j, k;
    for(k = 0; k < 4; k++) // de la 0 la 3 pentru ca sunt 4 piese in total
    {
//        int numar = nrPiesa(piese[k]);
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

/* Denis */

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

/* Denis */

void salvare_info()
{
    int index;
    ifstream citesc("index.txt");
    ofstream afiss("history.txt", ios::app);
    if(challengeNo < 10)afiss << "Challenge: " << challengeNo << "  | ";
    else afiss << "Challenge: " << challengeNo << " | ";
    char sir[8];
    strcpy(sir,timeToString().c_str());
    afiss << "Time: " << sir << " | Hint used: ";
    if(challengeNo < 17)afiss << "N/A";
        else if(rt == 0)afiss << "No ";
            else if(rt == 1)afiss << "Yes";
    afiss << " | Date: ";
    time_t now = time(0);
    tm* localtm = localtime(&now);
    afiss << asctime(localtm);
    afiss.flush();
    citesc >> index;
    index++;
    citesc.close();
    ofstream afisez("index.txt");
    afisez << index;
    afisez.flush();
    afisez.close();
}

/* Denis */

int page;
bool gameWon;
void castigare_challenge()
{
    char sir[8];
    strcpy(sir,timeToString().c_str());

    fout << challengeNo << " " << sir;
    fout << endl;
    fout.flush(); //file.flush() optiune pentru a salva continutul din fisier dupa scrierea in el
    //rezultate();
    salvare_info();

    setactivepage(3);
    cleardevice();
    readimagefile("./../resources/congrats.gif",0, 0, 900, 590);
    setbkcolor(COLOR(231, 221, 179));
    setcolor(COLOR(90, 108, 42));
    settextstyle(10, HORIZ_DIR,4);
    outtextxy(497,372,sir);
    setvisualpage(3);
}

/* Daniela */

void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,530);

    /// luam imaginile din memorie si le punem pe ecran
    for (int i = 0; i < 36; ++i)
        putimage(vCoord[i].x1, vCoord[i].y1, buffer[i], COPY_PUT);
}

/* Daniela */

void drawPieces (piesa & movablePiece) {
    // se deseneaza din memorie piesele
    // cu exceptia celei pe care s a dat click
    for (int i = 0; i < 4; ++i)
        if (& movablePiece != & piese[i])
            putimage(piese[i].x1,piese[i].y1,buffer[i + 36],COPY_PUT);
}

/* Denis */

void * vector_imagine[10];
int redimensionare_img_ch(char s[]) //Functia primeste linia challenge-ului si returneaza cate elemente are challenge-ul pentru a le centra
{
    char s_copie[100]; //facem copie pentru ca daca lucram pe s, dupa strtok s va deveni null
    strcpy(s_copie,s);
    int i = 0;
    char *p = strtok(s_copie, " ");
    while(p != NULL)
    {
        if(strcmp(p,"-1")!= 0)
                i++;
        p = strtok(NULL, " ");
    }
    return i;
}

/* Daniela */

struct dimensiuni{ //in acest struct vom pune pune coordonatele pieselor
    int a, b;
}vect[9];

/* Denis */

int k = 0;
int cont;
void afisare_challenge(int x, int y) // functia afiseaza dreptunghiul cu challenge-ul din partea dreapta in functie de butonul apasat(x)
{
    ifstream fin("challenge.txt");
    ifstream finn("dimensiuni.txt");
    if(y == 1)cont = 0;
    int i = 1 , a, b; // i - index pentru liniile din fisier, a, b - coordonatele care se schimba din 70 in 70 pentru fiecare patrat
    char sir[20] = "./../resources/"; // in sir ne vom crea adresa imaginilor din folder-ul resources
    char s[100];
    while(i < x) // parcurgem liniile din fisier si le ignoram pana ajungem la cea de care avem nevoie
    {
        fin.get(s, 100);
        fin.get();
        i++;
    }
    fin.get(s, 100); // in s se afla linia cu challege-ul de care avem nevoie

    if(y == 0) //daca sunt la prima intrare in challenge
        for(k = 1; k <= 8; k++) //parcurg fisierul cu dimensiuni si il pun in struct
            {
                finn >> vect[k].a;
                finn >> vect[k].b;
            }
    k = redimensionare_img_ch(s); // pun in k numarul de elemente din challenge
    a = vect[k].a; //initializez coordonatele lui a si b in functie de ce se afla in fisier pentru nr. respectiv de elemente
    b = vect[k].b;

    char *p = strtok(s, " "); // folosim un strtok pentru a pune in p fiecare imagine (de ex. 101.gif)
    while(p != NULL)
    {
        if(strcmp(p, "-1")!=0) // in fisier avem pun -1 ce reprezinta un patrat care se genereaza gol (ca un fel de spatiu)
        {
            strcat(sir,p);
            strcat(sir,".gif");
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

/* Denis */

void play_sound(int k)
{
    if(k % 2 != 0)PlaySound("hes-a-pirate.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    else //PlaySound("click.wav", NULL, SND_FILENAME|SND_ASYNC);
        PlaySound(NULL, NULL, SND_ASYNC);
}

/*Daca sunt la prima intrare (de on, sau off) salvez imaginea in memorie, iar daca nu afisez imaginea. Pentru a nu incepe de fiecare data melodia
(functia se apeleaza mereu in update page) imi iau un con_ant, si apelez melodia doar daca ultimul contor este diferit de cel actual (s-a dat click pe sunet).*/
void *soundon;
void *soundoff;
int con = -1, con_ant = -2, ok = 0, okk = 0;

void btn_snd()
{
    setcolor(15);
    rectangle(848, 18, 882, 52);
    if(con == -1 && ok == 0)
    {
        soundon = new char[imagesize(850, 20, 880, 50)];
        readimagefile("./../resources/soundon.gif", 850, 20, 880, 50);
        getimage(850, 20, 880, 50, soundon);
        ok++;
    }
    if(con == 0 && ok == 1)
    {
        soundoff = new char[imagesize(850, 20, 880, 50)];
        readimagefile("./../resources/soundoff.gif", 850, 20, 880, 50);
        getimage(850, 20, 880, 50, soundoff);
        ok++;
    }
        if(con % 2 != 0)
            putimage(850, 20, soundon, COPY_PUT);

        else
            putimage(850, 20, soundoff, COPY_PUT);
    okk++;
    //cout << con_ant << " " << con << endl;
}

/* Denis */

void *hint;
void *hint_img;
int f = 1, h = 1;
void hint_btn(int g)
{
    if(g == 0) // g este 0 pentru butonul de hint si 1 daca se apasa pe buton (imaginea de hint)
        if(f == 1)
        {
            hint = new char[imagesize(790, 541, 875, 583)];
            readimagefile("./../resources/hint_btn.gif", 790, 541, 875, 583);
            getimage(790, 541, 875, 583, hint);
            f = 0;
        }
        else putimage(790, 541, hint, COPY_PUT);
    else
    {
        ifstream cit("hint.txt"); //fisierul cu hinturile
        char p[16] = "./../resources/";
        char s[7];
        int index = 1, index_final = challengeNo - 16; // - 16 pentru ca de la challnge 17 incep sa apara hint uri si in fisier liniile sunt de la 1
        while(index <= index_final) // pargurg fisierul pana la linia care ma intereseaza
        {
            cit.get(s, 7);
            cit.get();
            index++;
        }
        strcat(p, s);
        p[21] = '\0';
        if(h == 1)
        {
            hint_img = new char[imagesize(835, 525, 895, 585)];
            readimagefile(p, 835, 525, 895, 585);
            getimage(835, 525, 895, 585, hint_img);
            h = 2;
        }
        else putimage(835, 525, hint_img, COPY_PUT);
    }
}

/* Denis */

bool trans_inminn() //verific daca a trecut un minut de joc
{   if(challengeNo > 16)
    {
        char sir[8];
        int minn;
        strcpy(sir,timeToString().c_str());
        char *p = strtok(sir, ":");
        minn = atoi(p);
        if(minn >= 1)return true;
    }
    return false;
}

/* Denis */

bool clickonhint()
{
    int x = mousex(), y = mousey();
    if(x >= 790 && x <= 875 && y >= 541 && y <= 583)
        return true;
    return false;
}

/* Denis */

bool clickonsound()
{
    int x = mousex(), y = mousey();
    if(getvisualpage() < 3)
        if(x >= 848 && x <= 882 && y >= 18 && y <= 52)
            {
                con++;
                if(con == 0)play_sound(2);
                if(con_ant != con)play_sound(con);
                con_ant = con;
                return true;
            }
    return false;

}

/* Denis */

bool clickonBACK()
{
    int x = mousex(), y = mousey();
    if(x >= 13 && x <= 101 && y >= 544 && y <= 581)
        return true;
    return false;
}

/* Daniela */

void updatePage (int & page, piesa & piece) {
    setactivepage(page);
    cleardevice();
    putimage(0,0,buffer[42],COPY_PUT);
    drawBoard();
    drawPieces(piece);
    afisare_challenge(challengeNo, 1);
    btn_snd(); drawTimer();
    if(trans_inminn() == 1 && rt == 0)hint_btn(0); //daca rt e 0 inseamna ca nu s-a apasat pe hint si afisez butonul
    else if(trans_inminn() == 1 && rt == 1)hint_btn(1); //daca rt e 1 inseamna ca s-a apasat si afisez imaginea
//    cout << time() << '\n';
    readimagefile(piece.pieceName,piece.x1,piece.y1,piece.x2,piece.y2);
    setvisualpage(page);
    page++;
}

/* Denis si Daniela */

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

/* Daniela */

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

/* Denis */

bool clickonFinish()
{
    int x = mousex(), y = mousey();
    if(x >= 370 && x <= 470 && y >= 544 && y <= 584) return true;
    return false;
}

/* Daniela */

piesa & clickedOnPiece () {
    int x = mousex(), y = mousey();
    for (int i = 0; i < 4; ++i)
        if (x >= piese[i].x1 && x <= piese[i].x2 && y >= piese[i].y1 && y <= piese[i].y2)
            return piese[i];
    return emptyPiece;
}

std::string isPieceInSquare (piesa & piece) {
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
                    return "rotation";
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
                return "inSquare";

            }
            if (patrate[i].piesa != & emptyPiece && index == -1)
                return "overlapping";

            if (index != -1) patrate[index].piesa = & emptyPiece;
            piece.x1 = patrate[i].x1; piece.y1 = patrate[i].y1;
            piece.x2 = patrate[i].x2; piece.y2 = patrate[i].y2;
            patrate[i].piesa = & piece;
            return "inSquare";
        }
    patrate[index].piesa = & emptyPiece;
    return "notInSquare";
}

/* Daniela */

void waitForMouseClick () {
    while (!ismouseclick(WM_LBUTTONDBLCLK) && !ismouseclick(WM_LBUTTONDOWN)
            && !ismouseclick(WM_RBUTTONDOWN)) {
        if (!gameWon)
        {
            drawTimer();
            if(trans_inminn() == 1 && rt == 0)hint_btn(0); //daca a trecut un minut afisez butonul de hint
        }
        delay (100);
    }
}

/* Daniela */

void mouseEvents () {
    bool pieceRotated;
    while (1) {
        pieceRotated = false;
        waitForMouseClick();
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_LBUTTONDOWN);
        if (gameWon) {
            clearmouseclick(WM_RBUTTONDOWN);
            if (clickonBACK())
                return;
            continue;
        }
        drawTimer();
        if (ismouseclick(WM_RBUTTONDOWN)) {
            cout << "RCLICK\n";
            pieceRotated = true;
        }
        piesa & piece = clickedOnPiece();
        if (& piece != & emptyPiece) { // am dat click pe o piesa
            std::cout << "clickedOnPiece\n";
            piesa initialPos = piece;
            while (!ismouseclick(WM_LBUTTONUP) && !pieceRotated)
                movePiece(piece);
            clearmouseclick(WM_LBUTTONUP);
            clearmouseclick(WM_RBUTTONDOWN);

            std::string res = isPieceInSquare(piece);
            if (res == "overlapping")
                piece = initialPos;
            if (page % 3 == 0)
                page = 1;
            updatePage(page, piece);

            // modificam imaginea piesei salvata in memorie pentru
            // ca fundalul sa fie transparent
            // extragem numarul piesei
            for (int i = 0; i < 4; ++i) {
                int numar = nrPiesa(piese[i]) - 1;
                buffer[numar + 36] = new char[imagesize(0, 0, 210, 210)];
                getimage(piese[i].x1, piese[i].y1, piese[i].x2, piese[i].y2, buffer[numar + 36]);
            }
        }
        else {
            std::cout << "NOTclickedOnPiece\n";
            if (clickonBACK() == 1) // se afiseaza pagina de nivele
                return;
            if(clickonFinish() == 1)
            //cout << patrate[0].piesa -> pieceName << " " << patrate[1].piesa -> pieceName << " " << patrate[2].piesa -> pieceName << " " << patrate[3].piesa -> pieceName << endl;
            if(strlen(patrate[0].piesa -> pieceName) != 0 && strlen(patrate[1].piesa -> pieceName) != 0 && strlen(patrate[2].piesa -> pieceName) != 0 && strlen(patrate[3].piesa -> pieceName) != 0)
            //cout << (strlen(patrate[2].piesa ->pieceName) == 0) << " ex" << endl;
            {
                matrici_piese();
                 if(verificare_solutie(challengeNo) == 1)
                    {
                        cout << "CHALLENGE CASTIGAT" << endl;
                        castigare_challenge();
                        gameWon = true;
                        continue;
                    }
                 else
                 {
                     cout << "MAI INCEARCA" << endl;
                     if(challengeNo < 17)readimagefile("./../resources/tryagain.gif", 750, 530, 880, 590); // au coordonate diferite pentru a nu se suprapune cu butonul de hint
                     else readimagefile("./../resources/tryagain.gif", 750, 475, 880, 535);
                 }
            }
            else cout << "Nu sunt puse toate piesele pe tabla!" << endl;
            if(clickonsound() == 1)
            {
                if (page % 3 == 0)
                    page = 1;
                updatePage(page,piece);
            }
            if(clickonhint() == 1) //daca dau click pe hint dau updatepage si afisez imaginea
                {
                    rt = 1;
                    if (page % 3 == 0)
                    page = 1;
                    updatePage(page, piece);
                    hint_btn(1);
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

/* Daniela */

void initializareValori () {
    // salvam coordonatele patratelor tablei
    patrate[0] = {195,65,405,275};
    patrate[1] = {425,65,635,275};
    patrate[2] = {195,295,405,505};
    patrate[3] = {425,295,635,505};

    for (int i = 0; i < 4; ++i) {
        patrate[i].piesa = & emptyPiece;
        piese[i].rotatie = 1;
    }

    gameWon = false; page = 2; k = 0;
    cont = 0;
    //con = -1, con_ant = -2;
    startTime = clock();
    unit = 1;
    unit *= CLOCKS_PER_SEC;
    rt = 0; h = 1; //reinitializez pentru fiecare challenge valorile pentru hint
}

/* Daniela */

void start_game (int level) {
    challengeNo = level;
    initializareValori();
    desenare_initiala();
    afisare_challenge(challengeNo, 0);
    btn_snd();
    if(okk == 1) play_sound(1);
    mouseEvents();
}
