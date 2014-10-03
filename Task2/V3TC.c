#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main () {
    int n;
    int b[5],l,i;
    scanf("%d",&n);
    l=ceil(sqrt(n));
    for (i=1;i<=4;i++) {
        while ((l*l)>n) {
            l+=-1;
        }
        n=n-(l*l);
        b[i]=l*l;
        l=l+1;
    }
    for (i=4;i>=1;i--) printf("%d ",b[i]);
    printf("\n");
    return 0;
}
