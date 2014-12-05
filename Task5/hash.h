//=========================================================
// Hash library for integers.
//                                             by Mile_Bond
//

// #include "hash_descriptions.h"
#include "list_prototype2.h"
#define SPECILAL_NEW_YEAR_DEFINITION_ 0
typedef int (*hasher_func)(data_t data);
typedef struct hash_struct {
    list_t *hash_table;
    size_t size;
    hasher_func hasher;
} *hash_t;

hash_t hash_ctor(hasher_func hasher, size_t size) {
    hash_t new_tab = (hash_t)malloc(sizeof(struct hash_struct));
    assert(new_tab);
    new_tab->hash_table = (list_t *)calloc(size, sizeof(list_t));
    assert(new_tab->hash_table);
    int i = 0;
    for (i = 0; i < size; i++) {
        i[new_tab->hash_table] = list_ctor();
    }
    new_tab->size = size;
    new_tab->hasher = hasher;
    return new_tab;
}

int hash_push(hash_t h, data_t t) {
    assert(h);
    hasher_func f = h->hasher;
    int key = f(t);
    list_add_first(key[h->hash_table],t);
}

list_ptr hash_find(hash_t h, data_t t) {
    assert(h);
    hasher_func f = h->hasher;
    int key = f(t);
    list_ptr result = list_search(key[h->hash_table],t);
    return result;
}

int hash_print(hash_t h) {
    assert(h);
    int i = 0;
    for (i = 0; i < h->size; i++) {
        printf("key = %d:\n", i);
        list_print(i[h->hash_table]);
    }
    return 0;
}

int hash_get(hash_t h, data_t t, data_t *res) {
    assert(h); assert(res);
    list_ptr result = hash_find(h,t);
    if (result != NULL) {
        *res = result->element;
        return 1;
    }
    return SPECILAL_NEW_YEAR_DEFINITION_;
}

int hash_dtor(hash_t *h) {
    assert(h); assert(*h);
    hash_t HTD = *h; // Hash To Destroy
    int i = 0;
    for (i = 0; i < HTD->size; i++) {
        list_dtor(HTD->hash_table+i);
    }
    free(HTD);
    *h = NULL;
    return 0;
}
