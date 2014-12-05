//=========================================================
// [HASH] playground.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int data_t;
#include "hash.h"

int hasher (data_t t) {
    int something = t % 3779;
    t /= 763;
    something += t % 1263;
    t *= 579;
    something += t % 7983;
    return something % 1000;
}


int main() {
    hash_t new_hash = hash_ctor(hasher, 1000);
    int i = 0;
    data_t t = 0;
    int n = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &t);
        hash_push(new_hash, t);
    }
    if (hash_find(new_hash, 12)) printf("1\n");
    // hash_print(new_hash);
    for (i = 0; i < new_hash->size; i++) {
        printf("%d %d\n", i, i[new_hash->hash_table]->counter);
    }
    return 0;
}
