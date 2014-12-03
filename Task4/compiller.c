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
#undef MY_COMPUTER_
#include "commands.h"
#include "..\Task3\stack_prototype3.h"
//=====================[ TYPEDEFS ]========================
typedef double arg_t;
typedef int lbl_t;
typedef int com_t;
#define SizeOffset sizeof(arg_t)/sizeof(com_t)   // Integers in Doubles.
typedef union transfer_temp{
    double dbl;
    struct {
        int itr[SizeOffset];
    };
} trns;
//===================[ DECLARATIONS ]======================
arg_t pop();
void dumparr(int *);
void push(arg_t);
int ScanFile(com_t **, lbl_t **);
int cleanup(com_t **, lbl_t **);
//======================[ STACK ]==========================
stack_t main_stack = NULL;
stack_t return_stack = NULL;
//====================[ REGISTERS ]========================
typedef enum registers_names {AX,BX,CX,DX,NL} registers;
arg_t reg[5] = {0};
registers register_num;
//=========================================================

int main() {
    main_stack = stack_ctor(sizeof(arg_t));
    return_stack = stack_ctor(sizeof(com_t*));
    //system("asm-part.exe");

    int i = 0;       // just useful variable
    arg_t arg;       // contain argument
    lbl_t lbl;       // contain label
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
        DBG fprintf(stderr, "Alive in main loop. c = %d\n", c); //getchar();
        CommandLine += 1;
        switch (c) {
        case F_PUSH_:
            for (i = 0; i < SizeOffset; i++) {
                t.itr[i] = *(CommandLine);
                CommandLine += 1;
            }
            arg = t.dbl;
            push(arg);
            break;
        case F_PUSHX_:
            register_num = *(CommandLine);
            CommandLine += 1;
            push(reg[register_num]);
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
        case F_POP_:
            register_num = *(CommandLine);
            CommandLine += 1;
            reg[register_num] = pop();
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
            } else CommandLine += 1;
            break;
        case F_OUT_:
            arg = pop();
            printf("%g\n", arg);
            getchar(); // system("pause");
            push(arg);
            DBG StackDump(main_stack,StackOk(main_stack));
            DBG dumparr(CommandLine);
            break;
        case F_END_:
            cleanup(&CommandsBegin, &JumpLabels);
            return 0;
        case F_HALT_:
            cleanup(&CommandsBegin, &JumpLabels);
            return 0;
        default:
            fprintf(stderr, "Compilation error!!!\n");
        }
        DBG getchar();
    }
    return 0;
}

int cleanup(com_t **CommandLine, lbl_t **LabelList) {
    stack_dtor(&main_stack);
    stack_dtor(&return_stack);
    free(*CommandLine);
    free(*LabelList);
}

void dumparr(int *a) {
    int *b = a;
    while (*a != F_END_) {
        fprintf(stderr, "number %d\n", a-b);
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
    FILE *code = fopen("D:/Repository_iLab/iLab/Task4/Prog.ap", "r");
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

    //=====================================================
    // First two nums in th file are sizes of arrays. We
    // count them while assembling.
    int Size_Commands = 0, Size_Labels = 0;
    fscanf(code, "%d %d", &Size_Commands, &Size_Labels);
    fgetc(code); // == '\n';
    DBG fprintf(stderr, "Sizes: %d, %d\n", Size_Commands, Size_Labels);
    com_t *commline = (com_t *)malloc(Size_Commands*sizeof(com_t));
    lbl_t *lbl_arr = (lbl_t *)malloc(Size_Labels*sizeof(lbl_t));
    assert(commline); assert(lbl_arr);

    lbl_t lbl = 0;
    arg_t arg = 0;           // some temp variables
    trns temp;
    while (1) {
        com_t c = 0;
        fscanf(code, "%d", &c);
        DBG fprintf(stderr, "[ SFL ] counter: %d\n",counter);
        DBG fprintf(stderr, "[ SFL ] %d\n",c);
        if (c == F_PUSH_) {
            //=============================================
            // Here is commands with arguments of (arg_t)
            assert(commline);
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%lf", &arg);
            DBG fprintf(stderr, "[ arg ]      %g\n", arg);
            temp.dbl = arg;
            int i = 0;
            for (i = 0; i < SizeOffset; i++) {
                commline[counter] = temp.itr[i];
                counter += 1;
            }
        } else if (c == F_END_) {
            //=============================================
            // The 'END' part closes (code) and returns.
            commline[counter] = c;
            fclose(code);
            *CommandLine = commline;
            *LabelList = lbl_arr;
            return counter;/*
            return TEA_CUP_;
            return commline;  /// WTF does it must return?
            return lbl_arr;*/
        } else if (c == F_LABEL_) {
            //=============================================
            // Every label is a number of (unsigned int),
            // so we just remember place of this label
            // into (lbl_arr[lbl]).
            // We don't record labels in (commline).
            fscanf(code, "%d", &lbl);
            fgetc(code); // == '\n';
            lbl_arr[lbl] = counter; // <-- all sense here
        } else if (c == F_JUMP_ ||
                   c == F_JNZ_ ||
                   c == F_POP_ ||
                   c == F_PUSHX_ ||
                   c == F_CALL_) {
            //=============================================
            // Here is commands with (lbl_t) arguments.
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%d", &lbl);
            commline[counter] = lbl;
            counter += sizeof(lbl)/sizeof(com_t);
        } else {
            //=============================================
            // Here is a place for commands without
            // any argument.
            commline[counter] = c;
            counter += 1;
        }
    }
}
