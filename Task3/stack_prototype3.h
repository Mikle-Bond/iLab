#define TEA_CUP_                0
#define EMPTY_STACK_            1
#define COUNTER_NEGATIVE_       2
#define ORDER_CRASHED_          3
#define UNEXPECTED_END_         4
#define END_NOT_FOUND_          5
#define NO_STACK_               6
#define TAIL_CORRUPTION_        7

#define NULL_ELEM_              0


//+++++++++++++++++++=+[ !CAUTION! ]+++++++++++++++++++++++
//               IS UNDER CONSTRUCTION YET
//+++++++++++++++++++=+[ !CAUTION! ]+++++++++++++++++++++++


typedef void* stack_elem;
typedef int stack_counter;
typedef struct gabriel {
    struct gabrilel *next;
    stack_elem element;
    stack_counter counter;
} stack_chain;
typedef stack_chain* stack_ptr;
typedef struct header {
    stack_ptr head;
    void *united;
    size_t elem_size;
} stack_head;
typedef stack_head *stack_t;


//======================[ CHECK ]==========================
// Scanning whole stack for the corruptions
int StackOk(const stack_t stack_s) {
    if (stack_s == NULL) return NO_STACK_;
    stack_ptr stk = stack_s->head;
    //=====================================================
    // (stk) points to the stack
    if (stk == NULL) return NO_STACK_;
    //=====================================================
    // Top element is not a tail
    stack_ptr temp = stk;
    stack_ptr pre_temp = NULL; // needed to check a tail
    stack_counter cnt = temp->counter;

    if (temp->next == NULL
        && temp->element == 0
        && cnt == 0)
        return EMPTY_STACK_;
    //=====================================================
    // Counter is positive
    if (cnt < 0) return COUNTER_NEGATIVE_;
    //=====================================================
    // All elements in their order
    while ( temp != NULL && cnt >= 0 ) {
        if ( cnt == temp->counter ) {
            cnt -= 1;
            pre_temp = temp;
            temp = (stack_ptr)temp->next;
        } else {
            return ORDER_CRASHED_;
        }
    }
    //=====================================================
    // Tail element was founded
    if (temp != NULL) {
        return END_NOT_FOUND_;
    } else if (pre_temp->counter != 0 || pre_temp->element != NULL_ELEM_) {
        return TAIL_CORRUPTION_;
    }
    /*
    //=====================================================
    // Tail is in the end of stack
    if (cnt >= 0) return UNEXPECTED_END_;
    */
    //=====================================================
    // If we still alive, have a teatime :)
    return TEA_CUP_;
}


//======================[ DUMP ]===========================
// Analyzing (errcode) and giving info about it
void StackDump(const stack_t stk, int errcode) {
    /* print defines */ {
    #ifndef DO_STR_PTR_
        #define DO_STR_PTR_  fprintf(stderr, "       (%4d): [%9d] -> (0x%X)\n", stptr->counter, stptr->element, stptr->next)
    #endif // DO_STR_PTR_
    #define DO_HEAD_PTR_ fprintf(stderr, "[DUMP] Start of dumping...\n");\
                         fprintf(stderr, "       Header address: 0x%X\n", stk);\
                         fprintf(stderr, "       Top address: 0x%X\n", stptr);\
                         fprintf(stderr, "       Counter: %d\n", (stptr)->counter)
    }
    int temp = errcode; // this string came from the past.
    int ctr = 0;
    int i = 0;
    stack_ptr stptr = stk->head;
    fprintf(stderr, "[DUMP] Error message: ");
    switch (temp) {
    case TEA_CUP_:
        fprintf(stderr, "---no errors---\n");
        DO_HEAD_PTR_;
        fprintf(stderr, "[DUMP] List of elements:\n");
        while (stptr->next != NULL) {
            DO_STR_PTR_;
            stptr = (stack_ptr)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case COUNTER_NEGATIVE_:
        fprintf(stderr, "Counter corrupted\n");
        DO_HEAD_PTR_;
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case EMPTY_STACK_:
        fprintf(stderr, "Empty stack (NULL pointer)\n");
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case ORDER_CRASHED_:
        fprintf(stderr, "Elements not in order\n");
        DO_HEAD_PTR_;
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        ctr = stptr->counter;
        i=0;
        for (i=0; i<=ctr; i++) {
            DO_STR_PTR_;
            stptr = (stack_ptr)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case END_NOT_FOUND_:
        fprintf(stderr, "End label was not found\n");
        DO_HEAD_PTR_;
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        ctr = stptr->counter;
        i=0;
        for (i=0; i<=ctr; i++) {
            DO_STR_PTR_;
            stptr = (stack_ptr)stptr->next;
        }
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    case TAIL_CORRUPTION_:
        fprintf(stderr, "End label appeared earlier, then expected\n");
        DO_HEAD_PTR_;
        fprintf(stderr, "[DUMP] Trying to show non-corrupted part:\n");
        while (stptr != NULL) {
            DO_STR_PTR_;
            stptr = (stack_ptr)stptr->next;
        }
        fprintf(stderr, "[DUMP] Last element points to NULL\n");
        fprintf(stderr, "[DUMP] End of dump.\n");
        break;
    default:
        fprintf(stderr, "Error not described: %d\n", errcode);
        break;
    }
    #undef DO_STR_PTR_
    #undef DO_HEAD_PTR_
}


//======================[ ASRT ]===========================
// Main part of all crashes. If there any corruption in
// stack - then crash report will be gift and program
// will be stopped.
void assertion(stack_t stk, int line) {
    int temp = StackOk(stk);
    if (temp != TEA_CUP_) {
        fprintf(stderr, "[WARN] Stack was corrupted!\n");
        StackDump(stk, temp);
        fprintf(stderr, "[INFO] Problem was found in line %d\n", line);
        system("pause");
        exit(1);
    }

}


//======================[ PUSH ]===========================
// Create a new element and fill it with parameters.
// If something wrong - crash everything with exit(1).
int stack_push(stack_t stk, stack_elem elt) {
    int exitcode = StackOk(stk);
    if (exitcode == TEA_CUP_ || exitcode == EMPTY_STACK_) {
        stack_ptr new_stack = (stack_ptr)malloc(sizeof(stack_chain));
        assert(new_stack);
        new_stack->element = malloc(stk->elem_size);
        assert(new_stack->element);

        int i = 0;
        for (i = 0; i < stk->elem_size; i++) {
            *((char *) (new_stack->element + i)) = *((char *) (elt + i));
        }


        new_stack->next = (struct gabriel *)(stk->head);
        new_stack->counter = (stk->head)->counter + 1;
        stk->head = new_stack;
        return 0;
    } else {
        fprintf(stderr, "[WARN] Stack was corrupted!\n");
        StackDump(stk, exitcode);
        fprintf(stderr, "[INFO] Problem was found in line %d\n", __LINE__);
        system("pause");
        exit(1);
    }
}


//========================[ POP ]==========================
// Destroying head of stack and returning its containment
stack_elem stack_pop(stack_t stack_geted) {
    assertion(stack_geted, __LINE__);

    int i = 0;
    for (i = 0; i < stack_geted->elem_size; i++) {
        *((char *) (stack_geted->united + i)) = \
        *((char *) ((stack_geted->head)->element + i));
    }

    free((stack_geted->head)->element);
    stack_ptr nxt = (stack_ptr) (stack_geted->head)->next;
    free(stack_geted->head);
    stack_geted->head = nxt;
    return stack_geted->united;
}


//======================[ CTOR ]===========================
// Making stack ready to work.
// Returns 0, if all is good, and 1, in another case.
stack_t stack_ctor(size_t size_elem) {
    stack_t stk = (stack_t)malloc(sizeof(stack_head));
    int exitcode = 0;
    //=====================================================
    // Here is a tail of stack - sign, which tell us
    // that stack was created in right way.
    stack_ptr stack_tail = (stack_ptr)malloc(sizeof(stack_chain));
    assert(stack_tail);
    stack_tail->element = NULL;
    stack_tail->next = NULL;
    stack_tail->counter = 0;
    stk->head = stack_tail;
    stk->elem_size = size_elem;
    stk->united = malloc(sizeof(size_elem));
    return stk;
}


//======================[ DTOR ]===========================
// Only working stack can be destroyed. If it's
// not like this, program will be stopped.
int stack_dtor(stack_t *stack_geted) {
    int errcode = StackOk(*stack_geted);
    if (errcode == TEA_CUP_){
        while (((*stack_geted)->head)->next != NULL) {
            stack_pop(*stack_geted);
        }
        fprintf(stderr, "[INFO] Working stack was destroyed.");
    }
    if (errcode == TEA_CUP_ || errcode == EMPTY_STACK_) {
        free((*stack_geted)->head);
        free((*stack_geted)->united);
        free(*stack_geted);
        *stack_geted = NULL;
        return 0;
    } else {
        fprintf(stderr, "[WARN] Stack was corrupted!\n");
        StackDump(*stack_geted, errcode);
        fprintf(stderr, "[INFO] Problem was found in line %d\n", __LINE__);
        system("pause");
        exit(1);
    }
}
