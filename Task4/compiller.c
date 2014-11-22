//=========================================================
//                    STACK PROCCESSOR
// Here is simple emulator of processor, which uses stack
// from previous task. In another programs there are parts
// with assembler and disassembler.
//                                            by Mikle_Bond
//

//=====================[ INCLUDES ]========================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "commands.h"
#include "..\Task3\stack_prototype3.h"
//=====================[ TYPEDEFS ]========================
typedef double arg_t;
typedef int lbl_t;
typedef int com_t;
typedef union transfer_temp{
    double d;
    struct {
        int i1;
        int i2;
    };
} trns;
//===================[ DECLARATIONS ]======================
arg_t pop();
void push(arg_t);
int ScanFile(com_t **, lbl_t **);
//========================[ STACK ]========================
stack_t main_stack = NULL;
stack_t return_stack = NULL;
//=========================================================

int main() {
    main_stack = stack_ctor(sizeof(arg_t));
    return_stack = stack_ctor(sizeof(com_t*));
    //system("asm-part.exe");

    arg_t arg;       // contain arguments
    lbl_t lbl;       // contain labels
    trns t;          // needed to convert (int) in (double)
    com_t c = 0;     // contain command number

    //=====================================================
    // To work we need to remember jump points and commands
    lbl_t *JumpLabels;
    com_t *CommandLine, *CommandsBegin;
    // (CommandLine) is var, as not as (CommandBegins) is.
    ScanFile(&CommandsBegin, &JumpLabels);
    CommandLine = CommandsBegin;
    // I promise, that I won't change (CommandsBegin) ever!
    while (1) {
        c = *CommandLine;
        fprintf(stderr, "Alive in main loop. c = %d\n", c); //getchar();
        CommandLine += 1;
        switch (c) {
        case F_PUSH_:
            t.i1 = *(CommandLine);
            t.i2 = *(CommandLine+1);
            arg = t.d;
            CommandLine += sizeof(arg)/sizeof(*CommandLine);
            push(arg);
            break;
        case F_ADD_:
            push(pop()+pop());
            break;
        case F_CMP_:
            push(pop()-pop());
            break;
        case F_MUL_:
            push(pop()*pop());
            break;
        case F_JUMP_:
            lbl = *((lbl_t*)CommandLine);
            CommandLine = CommandsBegin + lbl;
            break;
        case F_RET_:
            CommandLine = *((com_t**)stack_pop(return_stack))+1;
            break;
        case F_CALL_:
            stack_push(return_stack, &CommandLine);
            CommandLine = CommandsBegin + JumpLabels[*((lbl_t *)CommandLine)];
            break;
        case F_JNZ_:
            if (pop()) {
                CommandLine = CommandsBegin + JumpLabels[*((lbl_t *)CommandLine)];
            }
            break; // <<<---- I HAVE BEEN LOOKING FOR IT FOR A LOOOOOOOONG TIME!!!
        case F_OUT_:
            arg = pop();
            printf("%g\n", arg);
            getchar(); // system("pause");
            push(arg);
            StackDump(main_stack,StackOk(main_stack));
            dumparr(CommandLine);
            break;
        case F_END_:
            stack_dtor(&main_stack);
            return 0;
        case F_HALT_:
            stack_dtor(&main_stack);
            return 0;
        }
    }
    return 0;
}

void dumparr(int *a) {
    while (*a != F_END_) {
        fprintf(stderr, "[ SFL ] %d\n",*a);
        fprintf(stderr, "[ arg ]      %g\n", *(arg_t*)a);
        a++;
    }
}

arg_t pop() {
    arg_t arg = *((arg_t *)stack_pop(main_stack));
    return arg;
}
void push(arg_t arg) {
    stack_push(main_stack, &arg);
}


//=======================[ SCAN ]==========================
// ScanFile() takes two arguments - arrays for commands and
// for labels, and fills it up.
int ScanFile(com_t **CommandLine, lbl_t **LabelList) {
    /*----[ SOME DEFINES ]----*/ {
    #define COMMLINE_REALLOC_ \
        if (counter >= Size_Commands) {\
            Size_Commands += 10;\
            commline = (com_t *)realloc(commline, (Size_Commands+3)*sizeof(com_t));\
        } assert(commline)
    #define LBLARR_REALLOC_ \
        if (lbl>=Size_Labels) {\
            Size_Labels += 10;\
            lbl_arr = (lbl_t *)realloc(lbl_arr, (Size_Labels+3)*sizeof(lbl_t));\
        } assert(lbl_arr)
    }
    FILE *code = fopen("Prog.ap", "r");
    /*----[ SOME ASSERTS ]----*/ {
        assert(code);
        int lll = fgetc(code);
        if (lll == EOF) exit(1);
        ungetc(lll,code);
    }
    //=====================================================
    // So, we need two arrays and two counters - for
    // commands and for labels, vars to contain them, and
    // (temp) - to transfer (double) to (int).
    int counter = 0;
    int Size_Commands = 10, Size_Labels = 10;
    com_t *commline = (com_t *)malloc(Size_Commands*sizeof(com_t));
    assert(commline);
    lbl_t *lbl_arr = (lbl_t *)malloc(Size_Labels*sizeof(lbl_t));
    lbl_t lbl = 0;
    arg_t arg = 0;
    trns temp;
    while (1) {
        com_t c = 0;
        fscanf(code, "%d", &c);
        fprintf(stderr, "[ SFL ] %d\n",c);
        if (c == F_PUSH_) {
            //=============================================
            // At first we expand array, and after that
            // put the commands.
            assert(commline);
            commline[counter] = c;
            counter += 1;

            fscanf(code, "%lf", &arg);
            fprintf(stderr, "[ arg ]      %g\n", arg);
            temp.d = arg;
            commline[counter] = temp.i1;
            commline[counter+1] = temp.i2;
            counter += sizeof(arg_t)/sizeof(com_t);
        } else if (c == F_END_) {
            //=============================================
            // END means end. The end.
            commline[counter] = c;
            fclose(code);
            *CommandLine = commline;
            *LabelList = lbl_arr;
            return counter;
            return TEA_CUP_;
            return commline;  /// WTF does it must return?
            return lbl_arr;
        } else if (c == F_LABEL_) {
            //=============================================
            // Every label is a number of (unsigned int),
            // so we just remember place of this label
            // into (lbl_arr[lbl]).
            // We don't record it in (commline).
            fscanf(code, "%d", &lbl);
            fgetc(code); // == '\n';
            LBLARR_REALLOC_;
            lbl_arr[lbl] = counter; // <-- all sense here
        } else if (c == F_JUMP_ || c == F_JNZ_) {
            //=============================================
            // All JUMPs have the same structure in file.
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%d", &lbl);
            commline[counter] = lbl;
            counter += sizeof(lbl)/sizeof(com_t);
        } else {
            //=============================================
            // Here is a place for another functions.
            commline[counter] = c;
            counter += 1;
        }
        COMMLINE_REALLOC_;
    }
    #undef COMMLINE_REALLOC_
    #undef LBLARR_REALLOC_
}
