//
// Created by danie on 20.12.2022.
//

#include "Menu.h"

Menu::Menu() {
    this->bkgImage = new char [imagesize(0, 0, 900, 590)];

    readimagefile("./../resources/startgame.gif",0, 0, 900, 590);
    getimage(0, 0, 900, 590,this->bkgImage);
}

void Menu::draw() {
    putimage(0,0,this->bkgImage,COPY_PUT);
}

bool Menu::clickonBACK()
{
    int x = mousex(), y = mousey();
    if(x >= 13 && x <= 101 && y >= 544 && y <= 581)
        return true;
    return false;
}

bool Menu::clickonPlay()
{
    int x = mousex(), y = mousey();
    if (x >= 345 && x <= 545 && y >= 167 && y <= 255) return true;
    return false;
}

bool Menu::clickonRules()
{
    int x = mousex(), y = mousey();
    if (x >= 345 && x <= 545 && y >= 295 && y <= 385) return true;
    return false;
}

bool Menu::clickonExit()
{
    int x = mousex(), y = mousey();
    if (x >= 740 && x <= 875 && y >= 500 && y <= 565) return true;
    return false;
}

void Menu::waitForMouseClick () { while (!ismouseclick(WM_LBUTTONDOWN)) { delay (100);} }

void Menu::mouseEvents () {
    while (1) {
        waitForMouseClick();
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_RBUTTONDBLCLK);
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_RBUTTONDOWN);
        if (this->rulesAreOn) {
            if (clickonBACK()) {
                this->draw();
                this->rulesAreOn = false;
            }
            continue;
        }
        if (clickonPlay()) {
            std::cout << "play\n";
            this->levelWindow = new LevelsPage();
            this->levelWindow->mouseEvents();
            this->draw();
        }
        else if (clickonRules()) {
            std::cout << "rules\n";
            this->rulesAreOn = true;
            readimagefile("./../resources/rules.gif",0, 0, 900, 590);
        }
        else if (clickonExit()) {
            std::cout << "exit\n";
            exit(0);
        }
    }
}

Menu::~Menu() {
    delete this->bkgImage;
    delete this->levelWindow;
}