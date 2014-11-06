//=========================================================
//                    STACK PROCCESSOR
// Here is simple emulator of processor, which uses stack
// from previous task. In another programs there are parts
// with assembler and disassembler. Program is assembling
// every time before usage.
//                                            by Mikle_Bond
//


//+++++++++++++++++++++++[ NOTE ]++++++++++++++++++++++++++
// I think to unite ScanForLabels() and ScanForCommands()
// into one function - ScanFile(), and it will appear soon.
//+++++++++++++++++++++++[ NOTE ]++++++++++++++++++++++++++


//=====================[ INCLUDES ]========================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "commands.h"
#include "..\Task3\stack_prototype2.h"
//=====================[ TYPEDEFS ]========================
typedef double arg_t;
typedef int lbl_t;
typedef union tranfer_temp{
    double d;
    struct {
        int i1;
        int i2;
    };
} trns;
//===================[ DECLARATIONS ]======================
arg_t pop();
void push(arg_t);
int *ScanForLabels();
int *ScanForCommands();
//========================[ STACK ]========================
stack_t main_stack = {0};
//=========================================================

int main() {

    //system("asm-part.exe");
    stack_ctor(&main_stack);

    arg_t arg;       // contain arguments
    lbl_t lbl;       // contain labels
    trns t;          // needed to convert (int) in (double)
    int c = 0;       // contain command number

    //=====================================================
    // To work we need to remember jump points and commands
    int *JumpLabels;
    int *CommandLine, *CommandsBegin;
    // (CommandLine) is a var, instead of (CommandBegins)
    JumpLabels = ScanForLabels();
    CommandsBegin = ScanForCommands();
    CommandLine = CommandsBegin;
    while (1) {
        c = *CommandLine;
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
        case F_MUL_:
            push(pop()*pop());
            break;
        case F_JUMP_:
            lbl = *((lbl_t*)CommandLine);
            CommandLine = CommandsBegin + lbl;
            break;
        case F_JNZ_:
            if (pop()) {
                CommandLine = CommandsBegin + JumpLabels[*((lbl_t *)CommandLine)];
            }
        case F_OUT_:
            arg = pop();
            printf("%g\n", arg);
            getchar(); // system("pause");
            push(arg);
            StackDump(main_stack,StackOk(main_stack));
            break;
        case F_END_:
            stack_dtor(&main_stack);
            return 0;
        }
    }
    return 0;
}

//=========================================================
// Push() and Pop() are both took from [Task3]
arg_t pop() {
    return stack_pop(&main_stack);
}
void push(arg_t arg) {
    stack_push(&main_stack, arg);
}


//=======================[ LBLS ]==========================
// At first we need to find all labels in code. They are
// marked as F_LABEL_.
// Result is an array with command numbers, which labels
// are pointing to.
int *ScanForLabels() {
    FILE *code = fopen("Prog.ap", "r");
    //=====================================================
    // (counter) is a place of command in (CommandList)
    // array, and (max_lbl) - number of labels.
    int counter = 0, max_lbl = 0;
    lbl_t *lbl_arr = (lbl_t *)malloc(sizeof(lbl_t));
    lbl_t lbl = 0;   // we need only labels, but we must
    arg_t temp = 0;  // read everything, and args too.
    while (1) {
        int c = 0;
        fscanf(code, "%d", &c);
        // fprintf(stderr, "[ SFL ] %d\n",c);
        if (c == F_LABEL_) {
            fscanf(code, "%d", &lbl);
            // fprintf(stderr, "[ lbl ] %d\n",lbl);
            fgetc(code); // == '\n';
            if (lbl>max_lbl) {
                max_lbl = lbl;
                lbl_arr = (lbl_t *)realloc(lbl_arr, (max_lbl+1)*sizeof(lbl_t));
            }
            //=============================================
            // F_LABEL_ is not a command.
            lbl_arr[lbl] = counter;
        } else if (c == F_PUSH_) {
            counter += 1;
            //=============================================
            // F_PUSH_ waiting for (arg) of (arg_t) type:
            fscanf(code, "%lf", &temp);
            counter += sizeof(arg_t)/sizeof(int);
        } else if (c == F_END_) {
            fclose(code);
            return lbl_arr;
        } else {
            //=============================================
            // Here we eats another commands, integer arg,
            // e.g. args of F_JUMP_, F_JNZ, etc.
            counter += 1;
        }
    }
}


//=====================[ COMMANDS ]========================
// I don't know, what exactly it does, but I think that
// it does it wrong...
int *ScanForCommands() {
    FILE *code = fopen("Prog.ap", "r");
    //=====================================================
    // (commline) contains whole input from stream, except
    // labels.
    int *commline = (int *)malloc(sizeof(int));
    arg_t arg = 0;      // Now we really need to use args,
    lbl_t lbl = 0;      // and don't need labels.
    int counter = 0;
    trns t;
    while (1) {
        int c = 0;
        fscanf(code, "%d", &c);
        // fprintf(stderr, "[ SFC ] %d\n",c); system("pause");
        if (c == F_PUSH_) {
            commline = (int *)realloc(commline, ((counter+2+(sizeof(arg_t)/sizeof(int)))*sizeof(int)));
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%lf", &arg);
            t.d = arg;
            commline[counter] = t.i1;
            commline[counter+1] = t.i2;
            counter += sizeof(arg_t)/sizeof(int);
        } else if (c == F_END_) {
            commline[counter] = c;
            fclose(code);
            return commline;
        } else if (c == F_JUMP_) {
            commline = (int *)realloc(commline, ((counter+2+(sizeof(lbl_t)/sizeof(int)))*sizeof(int)));
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%d", &lbl);
            commline[counter] = lbl;
            counter += sizeof(lbl)/sizeof(int);
        } else if (c == F_JNZ_) {
            commline = (int *)realloc(commline, ((counter+2+(sizeof(lbl_t)/sizeof(int)))*sizeof(int)));
            commline[counter] = c;
            counter += 1;
            fscanf(code, "%d", &lbl);
            commline[counter] = lbl;
            counter += sizeof(lbl)/sizeof(int);
        } else if (c == F_LABEL_) {
            fscanf(code, "%d", &lbl);
        } else {
            commline = (int *)realloc(commline, ((counter+3)*sizeof(int)));
            commline[counter] = c;
            counter += 1;
        }
    }
}
