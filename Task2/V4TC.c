#include <stdio.h>

int v4tc() {
    int n=1, i=0, j=0, k=0;
    char p[1000], t;
    while ((t=getchar())!='\n') {
        p[n]=t;
        n+=1;
    }
    p[n]='\0';
    i=0;
    j=1;
    while (j<=n) {
        if ((p[j]>=65)&&(p[j]<=90)) {
        } else if ((p[j]>='a')&&(p[j]<='z')) {
        } else {
            k=j-1;
            while (k>i) {
                printf("%c",p[k]);
                k-=1;
            }
            i=j;
            printf("%c",p[j]);
        }
        j+=1;
    }
}

int main() {
    v4tc();
    return 0;
}

