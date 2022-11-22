#include <iostream>
#include <winbgim.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

/*void drawSolidLine (int x1,int y1,int x2,int y2) {
    setcolor(COLOR(75,205,244));
    setlinestyle(0,1,20);
    if (x1 == 400 || y1 == 300) {
        line(x1, y1, x2, y2);
        return;
    }
    rectangle (x1,y1,x2,y2);
}

void drawBoard () {
    drawSolidLine(200,120,600,480);
    drawSolidLine(400,120,400,480);
    drawSolidLine(200,300,600,300);

    setfillstyle(1,COLOR(49,195,232));
    bar (210,130,390,290);
    bar (410,130,590,290);
    bar (210,310,390,470);
    bar (410,310,590,470);
}

int main()
{
    initwindow(800,600,"Pirates Hide and Seek");
    setbkcolor(COLOR(247, 241, 226));
    cleardevice();

    drawBoard();

    getch();
    closegraph();
    return 0;
}*/

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b;
}
