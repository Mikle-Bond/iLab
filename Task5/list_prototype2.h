typedef data_t list_elem;
typedef int list_counter;
typedef struct elisabeth {
    struct elisabeth *next;
    struct elisabeth *prev;
    list_elem element;
    // list_counter counter;
} list_chain;
typedef list_chain* list_ptr;
typedef struct header {
    list_ptr head;
    list_ptr tail;
    list_counter counter;
} list_head;
typedef list_head *list_t;
/*
                                               .
        <<[ CTOR/DTOR SECTION ]>>              .         <<[ EVERYTHING ELSE ]>>
                                               .
.............................................................................................
                                               .
            |-----------|                      .
list_t ---> |list_head: |                      .
            |-----------|      |------------|  .   |------------|      |------------|
            |           |      | head == 0  |  .   |list_chain  |      |list_chain  | <-\
            |   head   ------> |------------|  .   |------------|      |------------|    \
            |           |      |    next    | ---> |    next    | ---> |    next   ----\  \
            |           | NULL <--- prev    | <--- |    prev    | <--- |    prev    |   \ |
            |           |      |------------|  .   |------------|      |------------|   | |
            |           |                      .                                        | |
            |-----------|  ===========================================================  | |
            |           |                      .                                        | |
            |           |      |------------|  .   |------------|      |------------|   | |
            |           |      | tail == 0  |  .   |list_chain  |      |list_chain  |   / |
            |   tail   ------> |------------|  .   |------------|      |------------|<-/  /
            |           | NULL <--- next    | <--- |    next    | <--- |    next    |    /
            |           |      |    prev    | ---> |    prev    | ---> |    prev   -----/
            |-----------|      |------------|  .   |------------|      |------------|
                                               .
                                               .

*/

int ListOk(const list_t lst) {
    assert(lst); assert(lst->head && lst->tail);
    int i = 0;
    list_ptr current = lst->head;
    list_ptr next = NULL;
    //=====================================================
    // Stage 1. Head analyzing.
    if (current->prev != NULL || current->element != 0) {
        fprintf(stderr, "Failed at the start))\n");
        exit(1);
    }
    //=====================================================
    // Stage 2. Body analyzing.
    for (i = 0; i < lst->counter; i++) {
        next = current->next;
        if (next == NULL) {
            fprintf(stderr, "End of list was not expected so fast.\n");
            exit(1);
        }
        if (next->prev != current) {
            fprintf(stderr, "Double links are more safety, when anyone changes them.\n");
            exit(1);
        }
        current = next;
    }
    //=====================================================
    // Stage 3. Tail analyzing.
    next = current->next; // if everything is OK, (next) == <tail>;
    if (next->next != NULL || next->element != 0) {
        fprintf(stderr, "Failed at the end((\n");
        exit(1);
    }
    //=====================================================
    // Stage 17.5. New Year is soon!!!
    if (next != lst->tail) {
        fprintf(stderr, "Everything was OK till the end, \nbut I think it should be the reason \nto remember the end of list...\n");
        exit(1);
    }
    return 0;
}

list_t list_ctor() {
    list_t new_list = (list_t)malloc(sizeof(list_head));
    assert(new_list);
    list_ptr head = (list_ptr)malloc(sizeof(list_chain));
    list_ptr tail = (list_ptr)malloc(sizeof(list_chain));
    assert(head && tail);
    new_list->head = head;
    new_list->tail = tail;
    new_list->counter = 0;
    head->element = 0;
    tail->element = 0;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
    return new_list;
}

int list_insert_after(list_ptr chain, list_elem data) {
    assert(chain);
    list_ptr prev = chain;
    list_ptr next = chain->next;
    list_ptr new_elem = (list_ptr)malloc(sizeof(list_chain));
    assert(new_elem);
    new_elem->element = data;
    new_elem->prev = prev;
    new_elem->next = next;
    prev->next = new_elem;
    next->prev = new_elem;
    return 0;
}


int list_insert_before(list_ptr chain, list_elem data) {
    assert(chain);
    list_ptr prev = chain->prev;
    list_ptr next = chain;
    list_ptr new_elem = (list_ptr)malloc(sizeof(list_chain));
    assert(new_elem);
    new_elem->element = data;
    new_elem->prev = prev;
    new_elem->next = next;
    prev->next = new_elem;
    next->prev = new_elem;
    return 0;
}


int list_add_first(list_t lst, list_elem data) {
    ListOk(lst);
    list_insert_after(lst->head, data);
    lst->counter += 1;
    return 0;
}

int list_add_last(list_t lst, list_elem data) {
    ListOk(lst);
    list_insert_before(lst->tail, data);
    lst->counter += 1;
    return 0;
}

list_elem list_remove(list_ptr chain) {
    assert(chain);
    list_ptr prev = chain->prev;
    list_ptr next = chain->next;
    assert(prev && next);
    list_elem ToRet = chain->element;
    free(chain);
    next->prev = prev;
    prev->next = next;
    return ToRet;
}

list_elem list_get_first(list_t lst) {
    ListOk(lst); assert(lst->counter);
    lst->counter -= 1;
    return list_remove((lst->head)->next);
}


list_elem list_get_last(list_t lst) {
    ListOk(lst); assert(lst->counter);
    lst->counter -= 1;
    return list_remove((lst->tail)->next);
}

list_ptr list_search(list_t lst, list_elem data) {
    ListOk(lst);
    list_ptr ToRet = lst->head;
    ToRet = ToRet->next;
    int i = 0;
    while (i < lst->counter && ToRet) {
        if (ToRet->element == data) break;
        i += 1;
        ToRet = ToRet->next;
    }
    if (ToRet == lst->tail) return NULL;
    return ToRet;
}

int list_print(list_t lst) {
    ListOk(lst);
    list_ptr current = (lst->head)->next;
    while (current != lst->tail) {
        printf("%d ", current->element);
        current = current->next;
    }
    printf("\n");
    return 0;
}

int list_dtor(list_t *lst) {
    assert(lst);
    list_t LTD = *lst; // List To Destroy
    ListOk(LTD);
    list_ptr current = LTD->head;
    list_ptr next = current->next;
    while (current != LTD->tail) {
        free(current);
        current = next;
        next = current->next;
    }
    free(current);
    free(LTD);
    *lst = NULL;
    return 0;
}
