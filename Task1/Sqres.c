#include <stdio.h>
#include <math.h>
#define LETTERS_IN_STRING_ 1

//#define MY_COMPUTER
#ifdef MY_COMPUTER
    #define DBG printf ("# ");
#else
    #define DBG if (0)
#endif

double X1;
double X2;
double D;
int COA;

int getclear (char*);
int getparams(char*, double*, double*, double*);
int Solve(double, double, double);

int main(){
    double a;
    double b;
    double c;
    char s[100];
    int n;
    getclear(s);

    n=getparams(s,&a,&b,&c);
    DBG printf("%lg %lg %lg\n",a,b,c);
    if (n!=0) {
        printf("Input not recognized");
        return 0;
    }
    Solve(a,b,c);
    if(COA==0){
        printf("No roots");
    }
    if (COA==2){
        printf("%lg %lg",X1,X2);
    }
    if(COA==1){
        printf("%lg",X1);
    }
    if(COA==-1){
        printf("Infinite");
    }
    return 0;
}

int Solve(double a, double b, double c){
    if (a==0){
        if (b!=0){
            X1=-c/b;
            COA=1;
        } else if (c==0){
            COA=-1;
        } else COA=0;
    }else{
        D=b*b-4*a*c;
        if(D==0){
            COA=1;
            X1=-b/(2*a);
        } else if(D>0){
            COA=2;
            X1=(-b+sqrt(D))/(2*a);
            X2=(-b-sqrt(D))/(2*a);
        } else COA=0;
    }
    return 0;
}

int getparams(char* s, double *a, double *b, double *c) {
    int i=0, j=1;
    int t, re;
    signed short int v=1; // sign of number
    double arg[4]={0,0,0,0};
    while (((s[i]<='9')&&(s[i]>='0'))||(s[i]==' ')||(s[i]==45)) {
        //========================================
        // If we are here, we have correct symbol
        //
        if (s[i]==' ') {
            //====================================
            // Two '_' in a row means
            // end of string
            //
            if (s[i-1]!=' ') {
                //================================
                // Here we are saving typed number
                //
                arg[j]=arg[j]*v;
                DBG printf("in summary %lg \n",arg[j]);
                v=1;
                j+=1;
            } else {
                break;
            }
        } else if (s[i]=='-') {
            if ((s[i-1]==' ')||(i==0)) {
                v=-1;
                DBG printf("one - \n");
            } else {
                return LETTERS_IN_STRING_;
            }
        } else {
            //====================================
            // Filling the current number
            //
            t=s[i]-'0';
            arg[j]=arg[j]*10+t;
            DBG printf("one %d \n",t);
        };
        i+=1;
    }
    DBG printf("ARGs: %lg %lg %lg\n",arg[1],arg[2],arg[3]);
    if ((s[i]==' ')){
        *a = arg[1]; //===========================
        *b = arg[2]; // Returning a, b, c
        *c = arg[3]; //
        return 0;
    }
    return LETTERS_IN_STRING_;
}

int getclear (char* s) { // Getting true string;
    int i=0;
    int n;
    char t;
    while ((t=getchar())!=10) {
        s[i]=t;
        i+=1;
    };
    n=i;
    for (i=n;i<n+4;i++) s[i]=' '; // Fills end of string with '_'
    DBG for (i=0;i<=n+4;i++) printf("%d ",s[i]);
    DBG printf("\n");
    return 0;
}
