//=========================================================
// Variant 1, Task C.
//
int v1tc () {
    int n;
    int t;

    scanf("%d",&n);
    while (n>0) {
        t=n%4;
        n=n/4;
        if (t==3) {
            n+=1;
        } else if (t==2) {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}

