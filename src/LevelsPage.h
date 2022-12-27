//
// Created by danie on 16.12.2022.
//

#ifndef PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H
#define PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H

#include <iostream>
#include <winbgim.h>
#include <fstream>
using namespace std;
struct button {
    int x1, y1, x2, y2;
    int level;
};
button emptyButton = {-1,-1,-1,-1,-1};

int fr[61], played[61], nivel_modificat;
void rezultate()
{
    int i, secc = 0, nrch, minn;
    char s[20];
    for(i = 1; i <= 61; i++)
        played[i] = 0;
       ifstream citt("rezultate.txt");
           while(citt.get(s, 20))
           {
           citt.get();
           char *p = strtok(s, " ");
           nrch = atoi(p);
           p = strtok(NULL, ":");
           minn = atoi(p);
           p = strtok(NULL, " ");
           secc = atoi(p);
           secc = secc + 60 * minn;
           if(fr[nrch] == 0)
           {
               fr[nrch] = secc;
               played[nrch]++;
           }
           else if(fr[nrch] > secc)
           {
               fr[nrch] = secc;
               played[nrch]++;
           }
            else played[nrch]++;

            //for(i = 1; i <= 60;i++)
                //if(played[i] != 0)cout << i << " " << played[i] << endl;
           //cout << nrch << " " << fr[nrch] << " " << secc << endl;
            }
            nivel_modificat = nrch;
       citt.close();
    //for(i = 1; i <= 60; i++)
        //if(fr[i] != 0)cout << i << " " << fr[i] << endl;
    //cout << "test" << endl;
}

class LevelsPage {
private:
    button levelButtons[61];
    void * levelPageImages[61];

    int levelPageImagesNo = 0;
    int lg = 0;
    bool history_clicked = false;
public:
    LevelsPage ();
    int clickedOnLevel ();
    void draw();
    bool clickonBACK();
    void waitForMouseClick ();
    void mouseEvents ();
    void ranking();
    void punesteluta(int nivel, int indent, int height);
    void drawhistory();

    ~LevelsPage() {
        for (int i = 0; i < 61; ++i)
            delete this->levelPageImages[i];
    }
};


#endif //PIRATES_HIDE_AND_SEEK_LEVELSPAGE_H
