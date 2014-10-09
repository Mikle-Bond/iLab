#include <stdio.h>

// YEAR 2008!

//=========================================================
// Variant 4. Task C.
//
// Writing sum of diagonals in square matrix.
//

int y8v4tc () {
    int n=0;
    scanf("%d",&n);
    int *a=(int *)calloc(2*n,sizeof(*a));
    int i=n, j=0;
    int temp=0;
    for (i=n; i>=1; i--) {
        for (j=i; j<=i+n-1; j++) {
            scanf("%d", &temp); // reading
            a[j]=a[j]+temp;
        }
    }
    for (i=1; i<2*n; i++) {
        printf("%d ", a[i]); // and writing.
    }
    free(a);
    return 0;
}

int main () {
    y8v4tc();
    return 0;
}
