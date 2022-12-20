//
// Created by danie on 16.12.2022.
//

#include "LevelsPage.h"

LevelsPage::LevelsPage() {
    this->levelPageImages[0] = new char [imagesize(0, 0, 900, 590)];
    for (int i = 1; i < 61; ++i)
        this->levelPageImages[i] = new char [imagesize(0,0,70,51)];

    readimagefile("./../resources/levelsBKG.gif",0, 0, 900, 590);
    getimage(0, 0, 900, 590,this->levelPageImages[this->levelPageImagesNo++]);

    char s[70] = "./../resources/nivele/nivel";
    strcpy (s + 29,".gif");
    int height = 170, indent = 30;
    for (int i = 0; i < 6; ++i) {
        for (int j = 1; j <= 10; ++j) {
            int nivel = i * 10 + j;
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

void LevelsPage::mouseEvents () {
    while (1) {
        waitForMouseClick();
        int level = clickedOnLevel();
        if (level != -1) {
            start_game(level);
            this->draw(); // daca am ajuns aici s a terminat jocul
        }
        else if (this->clickonBACK())
            return; // se intoarce la apelul mouseEvents din clasa Menu
        else {
            clearmouseclick(WM_LBUTTONDBLCLK);
            clearmouseclick(WM_RBUTTONDBLCLK);
            clearmouseclick(WM_LBUTTONDOWN);
            clearmouseclick(WM_RBUTTONDOWN);
        }
    }
}

void LevelsPage::draw() {
    setactivepage(1);
    cleardevice();
    putimage(0, 0,this->levelPageImages[0],COPY_PUT);
    setvisualpage(1);
}