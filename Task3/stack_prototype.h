typedef int stack_elem;
typedef int stack_counter;
typedef struct gabriel {
    struct gabrilel *next;
    stack_elem element;
    stack_counter counter;
} stack_chain;
typedef stack_chain* stack_t;

#define TEA_CUP_                0
#define EMPTY_STACK_            1
#define COUNTER_NEGATIVE_       2
#define ORDER_CRASHED_          3
#define UNEXPECTED_END_         4
#define END_NOT_FOUND_          5

int StackOk(const stack_t stk) {
    if (stk == NULL) return EMPTY_STACK_;
    stack_t temp = stk;
    stack_counter cnt = temp->counter;
    //=====================================================
    // Checking counter
    if (cnt < 0) return COUNTER_NEGATIVE_;
    //=====================================================
    // and all elements in their order
    while ( temp != NULL && cnt >= 0 ) {
        if ( cnt == temp->counter ) {
            cnt -= 1;
            temp = (stack_t)temp->next;
        } else {
            return ORDER_CRASHED_;
        }
    }
    //=====================================================
    // and the last of stack is correct
    if (temp != NULL) return END_NOT_FOUND_;
    if (cnt >= 0) return UNEXPECTED_END_;
    return TEA_CUP_;
}

void StackDump(const stack_t stk, int errcode) {
    int temp = errcode;
    int ctr = 0;
    int i = 0;
    stack_t stptr = stk;
    fprintf(stderr, "[DUMP] Error message: ");
    switch (temp) {
    case TEA_CUP_:
        fprintf(stderr, "---no errors---\n");
        fprintf(stderr, "[DUMP] Start of dumping...\n");
        fprintf(stderr, "       Top address: 0x%X\n", stk);
        fprintf(stderr, "       Counter: %d\n", (stk)->counter);
        fprintf(stderr, "[DUMP] List of elements:\n");
        while (stptr != NULL) {
            fprintf(stderr, "       (%4d): [%9d] -> (0x%X)\n", stptr->counter, stptr->element, stptr->next);
            stptr = (stack_t)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case COUNTER_NEGATIVE_:
        fprintf(stderr, "Counter corrupted\n");
        fprintf(stderr, "[DUMP] Start of dumping...\n");
        fprintf(stderr, "       Top address: 0x%X\n", stk);
        fprintf(stderr, "       Counter: %d\n", (stk)->counter);
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case EMPTY_STACK_:
        fprintf(stderr, "Empty stack (NULL pointer)\n");
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case ORDER_CRASHED_:
        fprintf(stderr, "Elements not in order\n");
        fprintf(stderr, "[DUMP] Start of dumping...\n");
        fprintf(stderr, "       Top address: 0x%X\n", stk);
        fprintf(stderr, "       Counter: %d\n", (stk)->counter);
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        ctr = stptr->counter;
        i=0;
        for (i=0; i<=ctr; i++) {
            fprintf(stderr, "       (%4d): [%9d] -> (0x%X)\n", stptr->counter, stptr->element, stptr->next);
            stptr = (stack_t)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case END_NOT_FOUND_:
        fprintf(stderr, "End label was not found\n");
        fprintf(stderr, "[DUMP] Start of dumping...\n");
        fprintf(stderr, "       Top address: 0x%X\n", stk);
        fprintf(stderr, "       Counter: %d\n", (stk)->counter);
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        ctr = stptr->counter;
        i=0;
        for (i=0; i<=ctr; i++) {
            fprintf(stderr, "       (%4d): [%9d] -> (0x%X)\n", stptr->counter, stptr->element, stptr->next);
            stptr = (stack_t)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case UNEXPECTED_END_:
        fprintf(stderr, "End label appeared earlier, then expected\n");
        fprintf(stderr, "[DUMP] Start of dumping...\n");
        fprintf(stderr, "       Top address: 0x%X\n", stk);
        fprintf(stderr, "       Counter: %d\n", (stk)->counter);
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        while (stptr != NULL) {
            fprintf(stderr, "       (%4d): [%9d] -> (0x%X)\n", stptr->counter, stptr->element, stptr->next);
            stptr = (stack_t)stptr->next;
        }
        fprintf(stderr, "[DUMP] Last element points to NULL\n");
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    }
}

void assertion(stack_t stk, int line) {
    int temp = StackOk(stk);
    if (temp != TEA_CUP_) {
        fprintf(stderr, "[WARN] Stack was corrupted!\n");
        StackDump(stk, temp);
        fprintf(stderr, "[INFO] Problem was found in line %d\n", line);
        exit(1);
    }

}

int stack_push(stack_t *stk, stack_elem elt) {
    if (*stk != NULL) assertion(*stk, __LINE__);
    stack_t new_stack = (stack_t)malloc(sizeof(*new_stack));
    new_stack->element = elt;
    new_stack->next = (*stk);
    if (*stk == NULL) {
        new_stack->counter = 0;
    } else {
        new_stack->counter = (*stk)->counter + 1;
    }
    *stk = new_stack;
}

stack_elem stack_pop(stack_t *stack_geted) {
    assertion(*stack_geted, __LINE__);
    stack_elem elt = (*stack_geted)->element;
    stack_t nxt = (stack_t) (*stack_geted)->next;
    free(*stack_geted);
    *stack_geted = nxt;
    return elt;
}

int stack_ctor(stack_t *stack_geted) {
    *stack_geted = NULL;
    return 0;
}

int stack_dtor(stack_t *stack_geted) {
    while (*stack_geted != NULL) {
        stack_pop(stack_geted);
    }
    return 0;
}
