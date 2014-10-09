#include <stdio.h.>

//=========================================================
// Variant 9. Task C.
//

typedef struct kagamine{
    char num;
    struct kagamine* next;
} chain;

int v9tc () {
    char c;
    //=====================================================
    // Reading first binary number
    chain *first_bin=NULL;
    while ((c=getchar())!='\n') {
        pastechain(c-48,&first_bin);
    }
    //=====================================================
    // Reading second binary number
    chain *second_bin=NULL;
    while ((c=getchar())!='\n') {
        pastechain(c-48,&second_bin);
    }
    //=====================================================
    // Firstly, we adding decimals which belongs
    // both of numbers
    int gap=0;
    int a=0,b=0;
    chain *answer=NULL;
    do {
        a=getchain(&first_bin);
        b=getchain(&second_bin);

        pastechain((a+b+gap)%2,&answer);
        gap=(a+b+gap)/2;
    } while ((first_bin != NULL)&&(second_bin != NULL)) ;
    //=====================================================
    // Then adding the last of each of numbers
    // (one or two of them will be empty)
    while (first_bin != NULL) {
        a=getchain(&first_bin);
        pastechain((a+gap)%2,&answer);
        gap=(a+gap)/2;
    }
    while (second_bin != NULL) {
        b=getchain(&second_bin);
        pastechain((b+gap)%2,&answer);
        gap=(b+gap)/2;
    }
    if (gap != 0) pastechain(gap,&answer);
    //=====================================================
    // And finally we have an answer!
    while (answer != NULL) {
        printf("%d",getchain(&answer));
    }
    return 0;
}

int pastechain (int c, chain **cur) {
    //=====================================================
    // Top chain remembers, who was her parent.
    // Parent of the last one is (NULL).
    if (*cur==NULL) {
        *cur = (chain *)malloc(sizeof(**cur));
        (**cur).next=NULL;
        (**cur).num=c;
    } else {
        chain *temp=(chain *)malloc(sizeof(*temp));
        (*temp).next=*cur;
        (*temp).num=c;
        *cur=temp;
    }
    return 0;
}

int getchain(chain **cur) {
    int num_cur=(**cur).num;
    chain *new_ch=(**cur).next;
    free(*cur); // don't forgetting to clean up))
    *cur=new_ch;
    return num_cur;
}

int main () {
    v9tc();
    return 0;
}

