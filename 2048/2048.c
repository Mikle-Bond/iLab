#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


        //directional keys
#define key_left    0x25
#define key_up      0x26
#define key_right   0x27
#define key_down    0x28
        // to quit
#define key_escape  0x1B
        // to make
#define LBOR_ printf("     ")
#define START_POS 0

typedef unsigned short int el_t;
int Arrow_Up = 1;
int Arrow_Down = 1;
int Arrow_Left = 1;
int Arrow_Right = 1;

void logo();
void Place_Rand(el_t**, int*);
int game_start();
int ArrOk(el_t**, int*);
void GoToXY(int, int);

int main () {
    logo();
    while (1) {
        game_start();
        //lose();
    }
    return 0;
}

void print_string(el_t a, el_t b, el_t c, el_t d) {
    switch (a) {
        case 0:
            printf("\xBA      ");
            break;
        case 2:
        case 4:
        case 8:
            printf("\xBA   %d  ", a);
            break;
        case 16:
        case 32:
        case 64:
            printf("\xBA  %d  ", a);
            break;
        case 128:
        case 256:
        case 512:
            printf("\xBA %d  ", a);
            break;
        case 1024:
        case 2048:
            printf("\xBA %d ", a);
            break;
    }
    switch (b) {
        case 0:
            printf("\xB3      ");
            break;
        case 2:
        case 4:
        case 8:
            printf("\xB3   %d  ", b);
            break;
        case 16:
        case 32:
        case 64:
            printf("\xB3  %d  ", b);
            break;
        case 128:
        case 256:
        case 512:
            printf("\xB3 %d  ", b);
            break;
        case 1024:
        case 2048:
            printf("\xB3 %d ", b);
            break;
    }
    switch (c) {
        case 0:
            printf("\xB3      ");
            break;
        case 2:
        case 4:
        case 8:
            printf("\xB3   %d  ", c);
            break;
        case 16:
        case 32:
        case 64:
            printf("\xB3  %d  ", c);
            break;
        case 128:
        case 256:
        case 512:
            printf("\xB3 %d  ", c);
            break;
        case 1024:
        case 2048:
            printf("\xB3 %d ", c);
            break;
    }
    switch (d) {
        case 0:
            printf("\xB3      \xBA\n");
            break;
        case 2:
        case 4:
        case 8:
            printf("\xB3   %d  \xBA\n", d);
            break;
        case 16:
        case 32:
        case 64:
            printf("\xB3  %d  \xBA\n", d);
            break;
        case 128:
        case 256:
        case 512:
            printf("\xB3 %d  \xBA\n", d);
            break;
        case 1024:
        case 2048:
            printf("\xB3 %d \xBA\n", d);
            break;
    }
}

void draw_small_borders() {
    int i=0;
    for (i=0; i<3; i++) { LBOR_; print_string(0,0,0,0); }
}

void logo() {

}

void first_draw() {
    int i=0, j=0;
    //=====================================================
    // Top Border
    LBOR_; printf("\xC9");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xD1");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xD1");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xD1");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xBB\n");

    //=====================================================
    // Making the rest
    for (j=1; j<4; j++) {
        draw_small_borders();
        LBOR_; printf("\xC7");
        for (i=1; i<=6; i++) printf("\xC4"); printf("\xC5");
        for (i=1; i<=6; i++) printf("\xC4"); printf("\xC5");
        for (i=1; i<=6; i++) printf("\xC4"); printf("\xC5");
        for (i=1; i<=6; i++) printf("\xC4"); printf("\xB6\n");
    }
    draw_small_borders();

    //=====================================================
    // Draw last line
    LBOR_; printf("\xC8");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xCF");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xCF");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xCF");
    for (i=1; i<=6; i++) printf("\xCD"); printf("\xBC\n");
}

void slide_line(el_t *a, el_t *b, el_t *c, el_t *d) {
    int i=0, j=0;
    el_t* x[4]={a,b,c,d};
    for (i=3; i>0; i--) {
        j=i-1;
        while (*x[j]==0 && j>=0) j-=1;
        if (j<0) break;
        if (*x[i]==*x[j]) {
            *x[i]+=*x[j];
            *x[j]=0;
        } else {
            if (*x[i]==0) {
                *x[i]=*x[j];
                *x[j]=0;
            }
        }
    }

}

void redraw(el_t **a) {
    int i=0;
    for (i=0; i<4; i++) {
        GoToXY(0,START_POS+i*4);
        print_string(a[1][i],a[2][i],a[3][i],a[4][i]);
    }
}

int game_start() {
    int i=0;
    first_draw();
    el_t GameMap[4][4]={\
    {0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0}};    // [column][row];
    int Counter=0;
    int c='\0';
    Place_Rand(GameMap, &Counter);
    // Place_rand(&GameMap, Counter);
    while (ArrOk(GameMap,&Counter)) {
        do {
            c=getch();
            if ((Arrow_Up) && (c==key_up)) break;
            if ((Arrow_Down) && (c==key_down)) break;
            if ((Arrow_Left) && (c==key_left)) break;
            if ((Arrow_Right) && (c==key_right)) break;
        } while (1);
        switch (c) {
            case key_down:
                for (i=0; i<4; i++)
                    slide_line(&GameMap[i][0],&GameMap[i][1],&GameMap[i][2],&GameMap[i][3]);
                break;
            case key_up:
                for (i=0; i<4; i++)
                    slide_line(&GameMap[i][3],&GameMap[i][2],&GameMap[i][1],&GameMap[i][4]);
                break;
            case key_right:
                for (i=0; i<4; i++)
                    slide_line(&GameMap[0][i],&GameMap[1][i],&GameMap[2][i],&GameMap[3][i]);
                break;
            case key_left:
                for (i=0; i<4; i++)
                    slide_line(&GameMap[3][i],&GameMap[2][i],&GameMap[1][i],&GameMap[0][i]);
                break;
        }
        redraw(GameMap);
    }
}

int ArrOk(el_t **a, int *c) {
    int i=0, j=0;
    Place_Rand(a,c);
    if (*c==16) {
        Arrow_Left=0;
        Arrow_Right=0;
        Arrow_Up=0;
        Arrow_Down=0;
        for (i=0; i<4; i++) {
            for (j=0; j<4; j++) {
                if (a[i][j]!=0) {
                    if ((!Arrow_Left)&&(i!=0)) {
                        if ((a[i-1][j]==0)||(a[i][j]==a[i-1][j])) {
                            Arrow_Left=1;
                        }
                    }
                    if ((!Arrow_Right)&&(i!=3)) {
                        if ((a[i+1][j]==0)||(a[i][j]==a[i+1][j])) {
                            Arrow_Right=1;
                        }
                    }
                    if ((!Arrow_Up)&&(j!=0)) {
                        if ((a[i][j-1]==0)||(a[i][j]==a[i][j-1])) {
                            Arrow_Up=1;
                        }
                    }
                    if ((!Arrow_Down)&&(j!=3)) {
                        if ((a[i][j+1]==0)||(a[i][j]==a[i][j+1])) {
                            Arrow_Down=1;
                        }
                    }
                }
            }
        }
    }
    if (Arrow_Down+Arrow_Left+Arrow_Right+Arrow_Up == 0) {
        return 0;
    } else {
        return 1;
    }
}

void Place_Rand(el_t **a, int *c) {
    el_t target;
    time_t t;
    int i=0, j=0;
    srand((unsigned) time(&t));
    if (rand()%7 == 3) {
        target=4;
    } else {
        target=2;
    }
    while (1) {
        i=rand()%4;
        j=rand()%4;
        if (a[i][j]==0) {
            a[i][j]=target;
            break;
        }
    }
    *c+=1;
}

void GoToXY(int column, int line) {
    // Create a COORD structure and fill in its members.
    // This specifies the new position of the cursor that we will set.
    COORD coord;
    coord.X = column;
    coord.Y = line;

    // Obtain a handle to the console screen buffer.
    // (You're just using the standard console, so you can use STD_OUTPUT_HANDLE
    // in conjunction with the GetStdHandle() to retrieve the handle.)
    // Note that because it is a standard handle, we don't need to close it.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord))
    {
        // Uh-oh! The function call failed, so you need to handle the error.
        // You can call GetLastError() to get a more specific error code.
        // ...
    }
}
