#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

void drawBoard () {
    setfillstyle(1,COLOR(84,197,210));
    bar (170,40,660,520);

    setfillstyle(1,COLOR(55,179,192));
    bar(195,65,405,275);
    bar(195,295,405,495);
    bar(425,65,635,275);
    bar(425,295,635,495);
}

int mat[6][6];

int main()
{
    initwindow(900,570,"Pirates Hide and Seek");
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();

    drawBoard();

    getch();
    closegraph();
    return 0;
}