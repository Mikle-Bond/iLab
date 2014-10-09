//=========================================================
// Variant 6. Task C.
//

int v6tc () {
    int n=0;
    int i=0, j=0, flag=1;
    unsigned int *a;
    scanf("%d",&n);
    a=malloc(sizeof(*a)*(n+1));
    for (i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (i=1; i<=n; i++) {
        flag=1;
        for (j=2; (j*j<=a[i])&&(flag); j++) {
            if (a[i]%(j*j)==0) {
                flag=0;
            }
        }
        if (flag) printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
