//
// Created by danie on 20.12.2022.
//

#ifndef PIRATES_HIDE_AND_SEEK_MENU_H
#define PIRATES_HIDE_AND_SEEK_MENU_H

#include <winbgim.h>
#include "LevelsPage.h"
#include <iostream>

class Menu {
private:
    void * bkgImage;
    LevelsPage * levelWindow = nullptr;

    bool rulesAreOn = false;
public:
    Menu ();

    void draw();
    bool clickonBACK();
    bool clickonPlay();
    bool clickonRules();
    bool clickonExit();
    void waitForMouseClick ();
    void mouseEvents ();

    ~Menu();
};


#endif //PIRATES_HIDE_AND_SEEK_MENU_H
