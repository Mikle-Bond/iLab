#include "tasks.h"

int main() {
    int e=0, k=0;
    while (1) {
    printf("\
\n\
/=================[ Year 2007 ]=================\\ \n\
|                                               |\n\
|   Variant 1: task C ..................... 1   |\n\
|   Variant 1: task D ..................... 2   |\n\
|   Variant 3: task C ..................... 3   |\n\
|   Variant 4: task C ..................... 4   |\n\
|   Variant 5: task D ..................... 5   |\n\
|   Variant 6: task C ..................... 6   |\n\
|   Variant 6: task D ..................... 7   |\n\
|   Variant 7: task C ..................... 8   |\n\
|   Variant 9: task C ..................... 9   |\n\
|                                               |\n\
|=================[ Year 2008 ]=================|\n\
|                                               |\n\
|   Variant 4: task C ..................... 10  |\n\
|                                               |\n\
|=================[  I N F O  ]=================|\n\
|                                               |\n\
|   Quick help is available :)                  |\n\
|   To exit type 0                              |\n\
|                                               |\n\
\\=================[  ]-   -[  ]=================/\n\
\n\
~# ");
    scanf("%d",&e); getchar();
    //e=getch();
    //e-=48;

    system("cls");
    switch (e) {
        case 1:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 1. Task C.\n\
||\n\
|| Checking, does number N could be imagined \n\
|| like a sum of powers of 4,\n\
|| like 1, 4, 16, etc.\n\
||------------\n\
|| Input:  N, 0 < N <= 2^31\n\
|| Output: 'YES' or 'NO'\n\
\n\n\
");
            v1tc();
            break;
        case 2:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 1. Task D.\n\
||\n\
|| 'Good' binary word is a word, where is no two '1' one by one in row.\n\
|| b(n,k) is a number of 'good' words with length n and k '1' in it.\n\
|| Example: b(4,2)=3\n\
||------------\n\
|| Input:  N, 0 <= N < 48\n\
|| Output: N+1 strings.\n\
||         Each string contains b(n,0) b(n,1) ... , where b(n,k) > 0\n\
\n\n\
");
            v1td();
            break;
        case 3:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 3. Task C.\n\
||\n\
|| As known, each natural number N could be presented as \n\
|| a sum of 4 squares of nonnegative numbers\n\
|| Example: 107 = 0 + 1 + 25 + 81\n\
||------------\n\
|| Input:  N, 0 < N <= 2000000\n\
|| Output: String of four squares a, b, c, d,\n\
           where a <= b <= c <= d, and a + b + c + d = N.\n\
\n\n\
");
            v3tc();
            break;
        case 4:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 4. Task C.\n\
||\n\
|| Reversing words in the string. \n\
|| Punctuation marks will be in their places.\n\
|| Example: 'Answer to Life, the Universe, and Everything!'\n\
|| Will become 'rewsnA ot efiL, eht esrevinU, dna gnihtyrevE!'\n\
||------------\n\
|| Input:  String with '\\n' in the end. Length is less then 1000.\n\
|| Output: Reverted string.\n\
\n\n\
");
            v4tc();
            break;
        case 5:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 5. Task D.\n\
||\n\
|| Reading the list of students  and their marks for CS.\n\
|| Sorting this list by names and by marks.\n\
|| Names is no longer, then 29 symbols.\n\
|| Example: \n\
|| Input:             Output:\n\
|| 3                 \xB3 alla 4\n\
|| lev 5             \xB3 boris 5\n\
|| alla 4            \xB3 lev 5\n\
|| boris 5           \xB3 \n\
||                   \xB3 boris 5\n\
||                   \xB3 lev 5\n\
||                   \xB3 alla 4\n\
|| In the second list students with the same marks sorted by name.\n\
||------------\n\
|| Input:  In first string - N, 0 < N < 10000. Next N strings\n\
           contains name of student and the mark from 1 to 10.\n\
|| Output: 2N+1 strings: two sorted lists with one empty line between them.\n\
\n\n\
");
            v5td();
            break;
        case 6:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 5. Task C.\n\
||\n\
|| Finding numbers without squares. \n\
|| Finds number, in multipliers of which \n\
|| is no any square more then 1.\n\
||------------\n\
|| Input:  In the first string - N, 0 < N <= 200,\n\
           in next string - N numbers.\n\
|| Output: Numbers with no squares in its multipliers.\n\
\n\n\
");
            v6tc();
            break;
        case 7:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 6. Task D.\n\
||\n\
|| Counting the number of decompositions of N \n\
|| Example: 5 has 7 decompositions:\n\
|| 5 = 4+1 = 3+2 = 3+1+1 = 2+2+1 = 2+1+1+1 = 1+1+1+1+1\n\
||------------\n\
|| Input:  N, 0 < N <= 100\n\
|| Output: Number of decompositions.\n\
\n\n\
");
            v6td();
            break;
        case 8:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 7. Task C.\n\
||\n\
|| Writing primes by their numbers.\n\
|| Will write N numbers in a row.\n\
|| Number one isn't prime.\n\
||------------\n\
|| Input:  N, 0 < N <= 10000\n\
           next - N integers - numbers of needed primes\n\
|| Output: N primes.\n\
\n\n\
");
            v7tc();
            break;
        case 9:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 9. Task C.\n\
||\n\
|| Summing two binary numbers.\n\
||------------\n\
|| Input:  Two strings with two numbers: a and b. Each in its row.\n\
           Each of strings is less then 1000 symbols in length.\n\
|| Output: One string - sum of a and b.\n\
\n\n\
");
            v9tc();
            break;
        case 10:
            printf("\n\
|| [  I N F O  ]\n\
|| Variant 8. Task C.\n\
||\n\
|| Summing numbers on diagonals of square matrix of numbers.\n\
|| Example for N = 4:\n\
||\n\
||  4   5   6   7  \n\
||    \\   \\   \\   \\\n\
||  3  \xC9\xCD\xCD\xCD\xD1\xCD\xCD\xCD\xD1\xCD\xCD\xCD\xD1\xCD\xCD\xCD\xBB \n\
||    \\\xBA \\ \xB3 \\ \xB3 \\ \xB3 \\ \xBA \n\
||  2  \xC7\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xB6 \n\
||    \\\xBA \\ \xB3 \\ \xB3 \\ \xB3 \\ \xBA \n\
||  1  \xC7\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xB6 \n\
||    \\\xBA \\ \xB3 \\ \xB3 \\ \xB3 \\ \xBA \n\
||     \xC7\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xC5\xC4\xC4\xC4\xB6 \n\
||     \xBA \\ \xB3 \\ \xB3 \\ \xB3 \\ \xBA \n\
||     \xC8\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xCF\xCD\xCD\xCD\xBC \n\
||------------\n\
|| Input:  Size of matrix N, 0 < N <= 50\n\
||         next N lines contains N numbers in each.\n\
|| Output: 2N-1 sums of diagonals.\n\
\n\n\
");
            y8v4tc();
            break;
        case 0:
            return 0;
        default:
            break;
    }
    printf("\n\n");
    system("pause");
    system("cls");
}
    return 0;
}

