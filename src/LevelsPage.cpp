//
// Created by danie on 16.12.2022.
//

#include "LevelsPage.h"
using namespace std;

void *ranking[5];
int levels_played, time_s, time_l, ch_time_s, ch_time_l, most_played1, most_played2;
//mostplayed1 -> cel mai jucat challenge, 2 -> de cate ori a fost jucat acel challenge
void LevelsPage::ranking()
{
    levels_played = 0;
    time_s = 999;
    time_l = 1;
    most_played1 = 0;
    most_played2 = 0;
    rezultate();
    int i;
    for(i = 1; i < 61; i++)
        if(fr[i] != 0)
        {
            levels_played++;
            if(time_s > fr[i])
                {
                    time_s = fr[i];
                    ch_time_s = i;
                }
            if(time_l < fr[i])
            {
                time_l = fr[i];
                ch_time_l = i;
            }
            if(played[i] > most_played2)
            {
                most_played1 = i;
                most_played2 = played[i];
            }
        }
    //cout << "Rezultate: " << levels_played << " " << time_s << " -> " << ch_time_s << " " << time_l << " -> " << ch_time_l << " " << most_played1 << " " << most_played2 << endl;
}

LevelsPage::LevelsPage() {
    this->levelPageImages[0] = new char [imagesize(0, 0, 900, 590)];
    readimagefile("./../resources/levelsBKG.gif",0, 0, 900, 590);
    getimage(0, 0, 900, 590,this->levelPageImages[this->levelPageImagesNo++]);
    //cout << fr[1] << "este" << endl;
    char s[70] = "./../resources/nivele/nivel";
    strcpy (s + 29,".gif");
    int height = 170, indent = 30;
    rezultate();
    for (int i = 0; i < 6; ++i) {
        for (int j = 1; j <= 10; ++j) {
            int nivel = i * 10 + j;
            this->levelPageImages[nivel] = new char[imagesize(indent + 15, height + 42, indent + 15 + 42, height + 42 + 15)];
            this->punesteluta(nivel, indent, height);

            //cout << fr[i * 10 + j] << endl;
//            if (j == 10)
//                nivel = (i + 1) * 10;
//            itoa(nivel, s + 27, 10);
//            if (nivel > 9)
//                strcpy(s + 29, ".gif");
//            else
//                strcpy(s + 28, ".gif");
//            readimagefile(s, indent, height, indent + 70, height + 51);
//            getimage(indent, height, indent + 70, height + 51,this->levelPageImages[this->levelPageImagesNo++]);
            this->levelButtons[++lg].x1 = indent;
            this->levelButtons[lg].y1 = height;
            this->levelButtons[lg].x2 = indent + 70;
            this->levelButtons[lg].y2 = height + 51;
            this->levelButtons[lg].level = nivel;
            indent += 85;
        }
        height += 61; indent = 30;
    }
    ranking();
}

int LevelsPage::clickedOnLevel() {
    int x = mousex(), y = mousey();
    for (int i = 1; i <= 60; ++i) {
        if (x >= this->levelButtons[i].x1 && x <= this->levelButtons[i].x2
            && y >= this->levelButtons[i].y1 && y <= this->levelButtons[i].y2)
            return this->levelButtons[i].level;
    }
    return -1;
}

bool LevelsPage::clickonBACK()
{
    int x = mousex(), y = mousey();
    if(x >= 13 && x <= 101 && y >= 544 && y <= 581)
        return true;
    return false;
}

void LevelsPage::waitForMouseClick () { while (!ismouseclick(WM_LBUTTONDOWN)) { delay (100);} }

bool clickonhistory()
{
    int x, y;
    x = mousex();
    y = mousey();
    if(x >= 794 && x <= 890 && y >= 538 && y <= 589)
        return true;
    return false;
}

void LevelsPage::drawhistory()
{
    char s[40];
    strcpy(s, "Challenges played: ");
    itoa(levels_played, s + 19, 10);
    strcat(s, "/60");
    setbkcolor(COLOR(127, 51, 0));
    setcolor(WHITE);
    settextstyle(8, HORIZ_DIR,1);
    outtextxy(316, 80, s);

    int height = textheight(s);
    if(time_s != 999)
    {
    s[0] = '\0';
    strcpy(s, "Shortest time spent: ");
    itoa(time_s, s + 21, 10);
    strcat(s, " sec");
    outtextxy(316, 80 + height, s);
    }
    else outtextxy(316, 80 + height, "Shortest time spent: N/A");

    if(time_s != 999)
    {
    s[0] = '\0';
    strcpy(s, "Shortest time challenge: ");
    itoa(ch_time_s, s + 25, 10);
    outtextxy(316, 80 + 2 * height, s);
    }
    else outtextxy(316, 80 + 2 * height, "Shortest time challenge: N/A");

    if(time_l != 1)
    {
    s[0] = '\0';
    strcpy(s, "Longest time spent: ");
    itoa(time_l, s + 20, 10);
    strcat(s, " sec");
    outtextxy(316, 80 + 3 * height, s);
    }
    else outtextxy(316, 80 + 3 * height, "Longest time spent:  N/A");

    if(time_l != 1)
    {
    s[0] = '\0';
    strcpy(s, "Longest time challenge: ");
    itoa(ch_time_l, s + 24, 10);
    outtextxy(316, 80 + 4 * height, s);
    }
    else outtextxy(316, 80 + 4 * height, "Longest time challenge:  N/A");

    if(most_played1 != 0)
    {
    s[0] = '\0';
    strcpy(s, "Most played challenge: ");
    itoa(most_played1, s + 23, 10);
    outtextxy(316, 80 + 5 * height, s);
    }
    else outtextxy(316, 80 + 5 * height, "Most played challenge: N/A");

    if(most_played2 != 0)
    {
    s[0] = '\0';
    strcpy(s, "Played: ");
    itoa(most_played2, s + 8, 10);
    strcat(s, " times");
    outtextxy(316, 80 + 6 * height, s);
    }
    else outtextxy(316, 80 + 6 * height, "Played: N/A");

    ifstream cit("index.txt");
    int index;
    cit >> index;
    int hei = 315;
    char p[200], k[200];
    ifstream fin("history.txt");
    int i = 1;
    while(i <= index - 12)
    {
        fin.get(k, 200);
        fin.get();
        i++;
    }
    for(i = 0; i < 12; i++)
    {
        fin.get(k, 200);
        fin.get();
        strcpy(p, k);
        outtextxy(25, hei, p);
        hei = hei + textheight(p);
    }

}
void LevelsPage::mouseEvents () {
    while (1) {
        waitForMouseClick();
        if(this->history_clicked == true)
        {
            clearmouseclick(WM_LBUTTONDBLCLK);
            clearmouseclick(WM_LBUTTONDOWN);
            if (clickonBACK())
                {
                    history_clicked = false;
                    this -> draw();
                }
            continue;
        }
        int level = clickedOnLevel();
        if (level != -1) {
            start_game(level);
            this->draw(); // daca am ajuns aici s a terminat jocul
        }
        else if (this->clickonBACK())
            return; // se intoarce la apelul mouseEvents din clasa Menu
        else if(clickonhistory() == 1)
            {
                this->history_clicked = true;
                setactivepage(5);
                readimagefile("./../resources/history.gif", 0, 0, 900, 590);
                ranking();
                this->drawhistory();
                setvisualpage(5);
            }
        else {
            clearmouseclick(WM_LBUTTONDBLCLK);
            clearmouseclick(WM_RBUTTONDBLCLK);
            clearmouseclick(WM_LBUTTONDOWN);
            clearmouseclick(WM_RBUTTONDOWN);
        }
    }
}

void LevelsPage::punesteluta(int nivel, int indent, int height)
{
    if(fr[nivel] >= 1 && fr[nivel] <= 30)
        {
        readimagefile("./../resources/3a.gif",indent + 15, height + 42, indent + 15 + 42, height + 42 + 15);
        getimage(indent + 15, height + 42, indent + 15 + 42, height + 42 + 15, this->levelPageImages[nivel]);
        }
    else
        if(fr[nivel] > 30 && fr[nivel] <= 60)
            {
                    readimagefile("./../resources/2a.gif",indent + 15, height + 42, indent + 15 + 42, height + 42 + 15);
                    getimage(indent + 15, height + 42, indent + 15 + 42, height + 42 + 15, this->levelPageImages[nivel]);
            }
        else
            if(fr[nivel] > 60)
                {
                    readimagefile("./../resources/1a.gif",indent + 15, height + 42, indent + 15 + 42, height + 42 + 15);
                    getimage(indent + 15, height + 42, indent + 15 + 42, height + 42 + 15, this->levelPageImages[nivel]);
                }
        else
            if(fr[nivel] == 0)
            {
                    readimagefile("./../resources/0a.gif",indent + 15, height + 42, indent + 15 + 42, height + 42 + 15);
                    getimage(indent + 15, height + 42, indent + 15 + 42, height + 42 + 15, this->levelPageImages[nivel]);
            }
}

void LevelsPage::draw() {
    setactivepage(1);
    cleardevice();
    rezultate();
    putimage(0, 0,this->levelPageImages[0],COPY_PUT);
    int height = 170, indent = 30;
    for (int i = 0; i < 6; ++i) {
        for (int j = 1; j <= 10; ++j) {
                if(i*10 + j != nivel_modificat)
                    putimage(indent + 15, height + 42, this->levelPageImages[i*10+j], COPY_PUT);
                else punesteluta(i * 10 + j, indent, height);
        indent += 85;
        }
    height += 61; indent = 30;
    }
    setvisualpage(1);
}


