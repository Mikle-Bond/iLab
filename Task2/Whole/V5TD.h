//=========================================================
// Variant 5. Task C.
//

typedef struct karoline {
    char name[30];
    unsigned short int num;
} elem;

int compare(char*, char*);
int qsort_name(elem*, int* , int, int);
int qsort_num(const elem*, int*, int);

int v5td () {
    int n=0;
    int i=0, j=0;
    char t=0;
    //=====================================================
    // We have an array of complex elements:
    // one string and one number.
    scanf("%d", &n); getchar();
    elem *a = (elem *)calloc(sizeof(*a),n+1);
    //=====================================================
    // Reading section
    for (i=1; i<=n; i++) {
        j=0;
        while ((t=getchar())!=' ') {
            a[i].name[j]=t;
            j+=1;
        }
        a[i].name[j]='\0';
        scanf("%hu",&a[i].num);
        getchar();
    }
    //=====================================================
    // Next, we have an array (b), where we saving
    // order of elements in (a). At the beginning
    // this elements staying one by one
    int b[n];
    for (i=1; i<=n; i++) {
        b[i]=i;
    }
    //============[TEST]===============//
#define PRINT_MAS_ \
    for (i=1; i<=n; i++) {\
        j=0;\
        while ((t=a[b[i]].name[j])!='\0') {\
            printf("%c", t);\
            j+=1;\
        }\
        printf(" %d\n", a[b[i]].num);\
    }
    //============[TEST]===============//
    //PRINT_MAS_
    qsort_name(a,b,1,n);
    PRINT_MAS_
    printf("\n");
    qsort_num(a,b,n); // (qsort_num) is not a qsort))
    PRINT_MAS_
//#undef PRINT_MAS_
    return 0;
}

int qsort_name(elem *a, int *b, int be, int en) {
    //=====================================================
    // Here is simple Quick Sort, but with two exceptions:
    int i=be-1;
    int j=en+1;
    int temp=0;
    int t;
    char *p=a[b[en]].name;
    do {
        do {
            i+=1;
        } while ((compare(a[b[i]].name,p))&&(i<=en));
        do {
            j-=1;
        } while ((compare(p,a[b[j]].name))&&(j>=be));
        //=================================================
        // First: we're comparing the strings. Not numbers.
        if (i<j) {
            //=============================================
            // Second: we aren't changing array (a),
            // because it's harder, then just swaping.
            temp=b[i];
            b[i]=b[j];
            b[j]=temp;
        }
    } while (i<j);
    if (be<j) qsort_name(a,b,be,j);
    if (i<en) qsort_name(a,b,i,en);
    return 0;
}


int qsort_num(const elem *a, int *b, int n) {
    //=====================================================
    // Firstly, I thought to do second sort like a QSort,
    // but now it's just a simple bauble.
    int i=n;
    int j=1;
    int p=1;
    int temp=0;
    for (j=n; j>1; j--) {
        p=j;
        for (i=1; i<j; i++) {
            if (a[b[i]].num<a[b[p]].num) {
                p=i;
            }
        }
        if (j!=p) {
            //=============================================
            // In task said to save alphabetic order
            // of elements with the same number, so
            // we can't just replace the numbers.
            temp=b[p];
            for (i=p+1; i<=j; i++) {
                b[i-1]=b[i];
            }
            b[j]=temp;
        }
    }
    return 0;
}


int compare(char *a, char *b) {
    //=====================================================
    // This function says true, or (1), if (b) is more (a).
    int i=0;
    while ((a[i]!='\0')&&(b[i]!='\0')) {
        if (a[i]>b[i]) {
            return 0;
        } else if (a[i]<b[i]) {
            return 1;
        } else {
            i+=1;
        }
    }
    if (a[i]=='\0') {
        if (b[i]=='\0') {
            //=============================================
            // Here is the situation, when (a) equals (b).
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

