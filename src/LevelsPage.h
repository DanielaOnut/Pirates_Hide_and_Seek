//
// Created by danie on 16.12.2022.
//

#ifndef PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H
#define PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H

#include <iostream>
#include <winbgim.h>

struct button {
    int x1, y1, x2, y2;
    int level;
};
button emptyButton = {-1,-1,-1,-1,-1};

class LevelsPage {
private:
    button levelButtons[61];
    void * levelPageImages[61];

    int levelPageImagesNo = 0;
    int lg = 0;
public:
    LevelsPage ();

    int clickedOnLevel ();
    void draw();
    bool clickonBACK();
    void waitForMouseClick ();
    void mouseEvents ();

    ~LevelsPage() {
        for (int i = 0; i < 61; ++i)
            delete this->levelPageImages[i];
    }
};


#endif //PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H
