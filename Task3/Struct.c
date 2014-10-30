//=========================================================
//                      [Task 3]
// Here is simple demonstration and my "playground"
// We reading two stacks, dumping first one, and writing
// them back. That's all.
//                                            by Mikle_Bond

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack_prototype.h"

int main() {
    int i=0, n=0, m=0;
    stack_elem t=0;

    stack_t first = {0};
    stack_ctor(&first);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &t);
        stack_push(&first, t);
    }

    //=====================================================
    // Example of dump
    StackDump(first, StackOk(first));

    //=====================================================
    // Simple crash-test))

    stack_t temp = first->next;
    temp->next = NULL;


    stack_t *second = {0};
    stack_ctor(&second);
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &t);
        stack_push(&second, t);
    }

    for (i = 0; i < n; i++) {
        printf("%d ", stack_pop(&first));
    }
    printf("\n");
    stack_dtor(&first);

    for (i = 0; i < m; i++) {
        printf("%d ", stack_pop(&second));
    }
    printf("\n");
    stack_dtor(&second);

    return 0;
}

