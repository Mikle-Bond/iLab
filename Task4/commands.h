//=========================================================
// Debug info
#ifdef MY_COMPUTER_
    #define DBG fprintf(stderr, "- DBG - ");
#else
    #define DBG if(0)
#endif // MY_COMPUTER_

//=========================================================
// Command codes:
/*
╔════════╤════════════╤══════╤══════════════════════╗
║ define |    NAME    | CODE |        uses          ║
╟────────┼────────────┼──────┼──────────────────────╢
║        |            |      |                      ║ */
#define    NO_CMD_       -1     // no use

#define    F_PUSH_        1     // PUSH 12
#define    F_PUSHX_      12     // PUSH CX
#define    F_POP_        48     // POP AX

#define    F_LABEL_       7     // loop:
#define    F_JUMP_        6     // JUMP 15
#define    F_CMP_         8     // CMP
#define    F_JNZ_        11     // JNZ :loop
#define    F_CALL_       15     // CALL :loop
#define    F_RET_        16     // RET

#define    F_OUT_        77     // OUT

#define    F_ADD_         2     // ADD
#define    F_MUL_         4     // MUL
#define    F_HALT_       55     // HALT
#define    F_END_         3     // END

#define    F_REGISTER_  110     // as argument
#define    R_AX_        100     // AX
#define    R_BX_        101     // BX
#define    R_CX_        102     // CX
#define    R_DX_        103     // DX
#define    R_NL_        104     // no argument

#define    S_NEW_LINE_   250    // '\n'
