#include <stdio.h>
#include <assert.h>

//=========================================================
// Variant 6. Task D.
//
int v2td () {
    int n=0;
    int i=0, j=0;
    scanf("%d",&n);
    //=====================================================
    // First n cells of array - links to rows,
    // and row j have j cells in length
    //
    unsigned long **q=(unsigned long**)\
        calloc((n*(n+3)/2)*sizeof(**q)+\
        n*sizeof(*q),1);
    assert(q);
    q[1]=&q[n+1];
    for (i=2;i<=n;i++) {
        //=================================================
        // As I've said, row (j-1) have (j-1) cells
        q[i]=q[i-1]+i-1;
    }
    //=====================================================
    // Checking if we have access to whole array
    assert(q[n][n]==0);

    q[1][1]=1;
    for (j=2;j<=n;j++) {
        q[j][1]=1;
        for (i=2;i<j;i++) {
            assert(q[j][i-1]);
            if (j-i>=i) {
                q[j][i]=q[j][i-1]+q[j-i][i];
            } else {
                //=========================================
                // If it was a full array (as in task said)
                // (q[a][b]) where b>a, equals (q[a][b-1])
                // and in end: (q[a][a]);
                q[j][i]=q[j][i-1]+q[j-i][j-i];
            }
        }
        //=================================================
        // (q[j][j-j])==1, so
        q[j][j]=q[j][j-1]+1;
    }
    printf("%lu",q[n][n]);
    free(q);
    return 0;
}


int main () {
    v2td();
    return 0;
}

