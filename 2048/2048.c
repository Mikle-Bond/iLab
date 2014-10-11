#include <stdio.h>

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
int Arrow_UpDown = 1;
int Arrow_LeftRight = 1;

void logo();
int game_start();

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
        gotoxy(0,START_POS+i*4);
        print_string(a[1][i],a[2][i],a[3][i],a[4][i]);
    }
}

int game_start() {
    first_draw();
    el_t GameMap[4][4]={\
    {0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0},\
    {0,0,0,0}};    // [column][row];
    int Counter=0;
    int c='\0';
    Place_rand(GameMap, Counter);
    // Place_rand(&GameMap, Counter);
    while (ArrOk(GameMap,Counter)) {
        do {
            c=getch();
            if ((Arrow_UpDown) && (c==key_down || c==key_up)) break;
            if ((Arrow_LeftRight) && (c==key_left || c==key_right)) break;
        } while (1);
        switch (c) {
            if (Arrow_UpDown) { case key_down:
                slide_line(&GameMap[1][1],&GameMap[1][2],&GameMap[1][3],&GameMap[1][4]);
                slide_line(&GameMap[2][1],&GameMap[2][2],&GameMap[2][3],&GameMap[2][4]);
                slide_line(&GameMap[3][1],&GameMap[3][2],&GameMap[3][3],&GameMap[3][4]);
                slide_line(&GameMap[4][1],&GameMap[4][2],&GameMap[4][3],&GameMap[4][4]);
                break;
            }
            if (Arrow_UpDown) { case key_up:
                slide_line(&GameMap[1][4],&GameMap[1][3],&GameMap[1][2],&GameMap[1][1]);
                slide_line(&GameMap[2][4],&GameMap[2][3],&GameMap[2][2],&GameMap[2][1]);
                slide_line(&GameMap[3][4],&GameMap[3][3],&GameMap[3][2],&GameMap[3][1]);
                slide_line(&GameMap[4][4],&GameMap[4][3],&GameMap[4][2],&GameMap[4][1]);
                break;
            }
            if (Arrow_LeftRight) { case key_right:
                slide_line(&GameMap[1][1],&GameMap[2][1],&GameMap[3][1],&GameMap[4][1]);
                slide_line(&GameMap[1][2],&GameMap[2][2],&GameMap[3][2],&GameMap[4][2]);
                slide_line(&GameMap[1][3],&GameMap[2][3],&GameMap[3][3],&GameMap[4][3]);
                slide_line(&GameMap[1][4],&GameMap[2][4],&GameMap[3][4],&GameMap[4][4]);
                break;
            }
            if (Arrow_LeftRight) { case key_left:
                slide_line(&GameMap[4][1],&GameMap[3][1],&GameMap[2][1],&GameMap[1][1]);
                slide_line(&GameMap[4][2],&GameMap[3][2],&GameMap[2][2],&GameMap[1][2]);
                slide_line(&GameMap[4][3],&GameMap[3][3],&GameMap[2][3],&GameMap[1][3]);
                slide_line(&GameMap[4][4],&GameMap[3][4],&GameMap[2][4],&GameMap[1][4]);
                break;
            }
        }
        redraw(GameMap);
    }

}

int ArrOk(el_t *a, int c) {
    Place_Rand(a,c);

}
