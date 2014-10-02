#include <stdio.h>
//=========================================================
// Variant 1, Task D.
//
int main () {
    int n;
    long a[100], b[100];
    long ToFuture, FromPrev;

    int i,j;

    //=====================================================
    // This is starting values of first two strings:
    // 1
    // 1 1
    b[1]=1; b[2]=0;
    a[1]=1; a[2]=1; a[3]=0;

    scanf("%d", &n);

    //=====================================================
    // First line will always be shown:
    printf("1\n");

    for (i=2; i<=n+1; i++) {
        j=1;
        //=================================================
        // Printing current line:
        while (a[j]!=0) {
            printf("%d ",a[j]);
            j+=1;
        }
        printf("\n");
        //=================================================
        // Idea is that we can get new line (n) like this:
        // n[j] = a[j] + b[j-1];
        // and then clone (a) to (b) and (n) to (a),
        // but this is not cool, so...
        ToFuture=1;
        for (j=2; j<=i; j++) {
            // we're saving (b[j]) with the reason
            // to place it in (ToFuture):
            FromPrev=b[j];
            b[j]=a[j];
            // now (ToFuture) contains (b[j-1]):
            a[j]=a[j]+ToFuture;
            // and we're saving (b[j]) in (ToFuture):
            ToFuture=FromPrev;
        }
        // and adding some nulls:
        a[i+2]=0; b[i+2]=0;
    }

    return 0;
}

