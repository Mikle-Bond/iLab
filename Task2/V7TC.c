#include <stdio.h>
#include <assert.h>
//=========================================================
// Variant 7. Task C.
//

int recheto (unsigned long long *a,
             unsigned long long needed) {
    //=====================================================
    // Getting number of simples
    // Gives the array of simples (a)
    // Returns the length of this array
    //
    unsigned long long i,t,k,m,n=needed*needed;
    char *b = (char*)calloc(n,sizeof(*b));
    assert(b);
    //=====================================================
    // Filling array of numbers
    b[2]=1;
    i=3;
    while (i<=n) {
            b[i]=1;
            i+=2;
    }
    //=====================================================
    // Crossing not simples from 3 to sqrt(n)
    i=3;
    a[1]=2; m=2;
    while ((t=i*i)<=n) {
    //t=i*i because i*2, i*3, etc we've already crossed
        if (b[i]!=0) {
            k=t;
            while (k<=n) {
                b[k]=0;
                k=k+i+i;
            }
            a[m]=i;
            m+=1;
        }
        i+=2;
    }
    //=====================================================
    // Collapsing the least of array
    while (i<=n && m<=needed+1) {
        if (b[i]!=0) {
            a[m]=i;
            m+=1;
        }
        i+=2;
    }
    free(b);
    return m-1;
}
int v7tc () {
    unsigned long long *a;
    unsigned long *b,num_of_anwers=0,max_simple=0;
    unsigned long leng,i;

    //=====================================================
    // Reading section
    //
    scanf("%d",&num_of_anwers);
    b=calloc(num_of_anwers,sizeof(*b));

    for (i=0; i<num_of_anwers; i++) {
        scanf("%d",&b[i]);
        if (b[i]>max_simple) max_simple=b[i];
    }

    //=====================================================
    // Counting simples
    //
    a=calloc(max_simple*2,sizeof(*a));
    assert(a);
    leng=recheto(a,max_simple);
    assert(leng>=max_simple);

    //=====================================================
    // Writing answers
    //
    for (i=0; i<num_of_anwers; i++) {
        printf("%llu ", a[b[i]]);
    }
    free(a);
    free(b);

    return 0;
}

int main () {
    v7tc();
    return 0;
}


