#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #define MY_COMPUTER_ 1
#include "commands.h"
#define LBL_MAX_LEN_ 20
struct lbls {
    char *labels[100];
    int counter;
    int curlbl;
} label_list = {0};

int strnom = 0;      // number of string - needs to be global.

int fill_lbl(FILE *);                                 // finds the labels and counts commands.
int my_strcomp(const char *, const char *);           // compares by first string.
int find_cmd(char *, int *, int *, FILE *, FILE *);   // returns command and its argument.

int main () {
    FILE *code, *recode;
    code = fopen("Prog.txt", "r"); assert(code);      // source file.
    recode = fopen("Prog.ap", "wb"); assert(recode);  // target file.
    int Number_Of_Commands = fill_lbl(code);          // needs to be written in the head of (recode).
    char cmd_txt[LBL_MAX_LEN_] = {'\0'};              // text buffer.
    int cmd_code = 0;                                 // assembled code of command.
    int errflag = 0;                                  // problems detector.
    int isarg = 0, arg = 0;                           // boolean indicator of argument and argument.

    //=====================================================
    // In head there are numbers of commands and labels
    fprintf(recode, "%d %d\n", Number_Of_Commands, label_list.counter);

    //=====================================================
    // Input/output block.
    do {/*
        cmd_txt[0] = '\0';
        cmd_txt[1] = '\0';
        cmd_txt[2] = '\0';
        cmd_txt[3] = '\0';
        cmd_txt[4] = '\0';*/
        fscanf(code, "%s", cmd_txt);
        strnom += 1;
        //=================================================
        // check the string for command
        cmd_code = find_cmd(cmd_txt, &isarg, &arg, code, recode);
        if (cmd_code == NO_CMD_) {
            //=============================================
            // logging errors
            fprintf(stderr, "%d: command not recognized: %s\n", strnom, cmd_txt);
            errflag = 1;
            char c = 0;
            do c = fgetc(code); while (c != '\n');
            ungetc(c, code);
        } else {
            //=============================================
            // writing assembled code
            fprintf(recode, "%c", cmd_code);
            DBG fprintf(stdout, "%d", cmd_code);
            if (isarg) {
                fprintf(recode, " %d", arg);
                DBG fprintf(stdout, " %d", arg);
            }
            fprintf(recode, "\n");
            DBG fprintf(stdout, "\n");
            if (cmd_code == F_END_) break;
        }
    } while (fgetc(code) != EOF && cmd_code != F_END_);
    if (cmd_code != F_END_) {
        fprintf(stderr, "%d: 'END' was expected, but 'EoF' was found.\n", strnom);
        errflag = 1;
    }
    fclose(code);
    fclose(recode);
    if (errflag) {
        system("del Prog.ap");
        return -1;
    }
    return 0;
}

//=========================================================
// Fills the (label_list). Also counts number of commands
// (especially, skipped strings).
int fill_lbl(FILE *code) {
    int Commands_counter = 0;
    int Last_Was_Func_With_Double_Arg = 0; // needed for command counting
    while (!feof(code)) {
        int buff = 0;
        char str[LBL_MAX_LEN_];
        // Firstly, let's eat some rubbish :)
        while((buff = fgetc(code)) == ' ' || buff == '\n') {
            DBG printf("I eat '%c'\n", buff);
        }
        if (buff == EOF) break;
        ungetc(buff, code);
        //=================================================
        // Is there a label?
        int len = 0;
        while ((buff = fgetc(code)) != '\n' && buff != EOF && buff != ' ') {
            str[len] = buff;
            len+=1;   // len = strlen(str);
        }
        str[len] = '\0';
        DBG printf("%s\n", str);
        if (str[len-1] == ':') {
            //=============================================
            // Labels have ':' at the end.
            label_list.labels[label_list.counter] = (char *)calloc(len, sizeof(char));
            int j = 0;
            for (j = 0; j < len; j++) label_list.labels[label_list.counter][j] = str[j];
            label_list.labels[label_list.counter][len-1] = '\0';
            DBG fprintf(stderr, "[ LBL ] %s\n",label_list.labels[label_list.counter]);
            label_list.counter += 1;
        } else {
            Commands_counter += 1;
            if (Last_Was_Func_With_Double_Arg && str[1] != 'X') {
                Commands_counter += 1;
            }
            Last_Was_Func_With_Double_Arg = my_strcomp("PUSH", str);
        }
    }
    label_list.curlbl = 0;
    rewind(code);
    return Commands_counter;
}

//=========================================================
// returns code of command
int find_cmd(char s[], int *bul, int *arg, FILE *code, FILE *recode) {
    *bul = 0; // is command needs an argument?
    DBG fprintf(stderr, "[ N E ] %s\n", s);
    if (my_strcomp(s+1, "X")) {
        *bul = 1;
        if(s[0] > 'D' || s[0] < 'A') return NO_CMD_;
        *arg = s[0] - 'A';
        return F_REGISTER_;
    } else if (my_strcomp(s, "PUSH")) {
        *bul = 1;
        if (fscanf(code, "%d", arg)) {
            return F_PUSH_;
        } else if (fscanf(code, "%s", s)) {
            int code_temp = find_cmd(s,bul,arg,code,recode);
            if (code_temp == F_REGISTER_) {
                // if(s[5] > 'D' || s[5] < 'A') return NO_CMD_;
                // *arg = s[5] - 'A';
                return F_PUSHX_;
            } else return NO_CMD_;
        }
    } else if (my_strcomp(s, "POP")) {
        // [POP] can be or an only command, or a command
        // with register. We will analyze next word after
        // [POP], and if there no register, we retell to
        // main next command.
        *bul = 1;
        int code_temp = NO_CMD_;           // contain next command.
        if (fscanf(code, "%s", s)) {
            code_temp = find_cmd(s,bul,arg,code,recode);
            if (code_temp == F_REGISTER_) {
                return F_POP_;
            }
        }
        // 'else' means, that there were another function,
        // and we should place F_POP_ before returning.
        fprintf(recode, "%c %c\n", F_POP_, R_NL_);
        DBG fprintf(stdout, "%d", F_POP_);
        DBG fprintf(stdout, " %d", R_NL_);
        DBG fprintf(stdout, "\n");
        strnom += 1;

        return code_temp;
    } else if (my_strcomp(s, "ADD")) {
        return F_ADD_;
    } else if (my_strcomp(s, "MUL")) {
        return F_MUL_;
    } else if (my_strcomp(s, "OUT")) {
        return F_OUT_;
    } else if (my_strcomp(s, "END")) {
        return F_END_;
    } else if (my_strcomp(s, "RET")) {
        return F_RET_;
    } else if (my_strcomp(s, "HALT")) {
        return F_HALT_;
    } else if (my_strcomp(s, "CMP")) {
        return F_CMP_;
    } else if (my_strcomp(s, "JUMP")) {
        *bul = 1;
        fscanf(code, "%d", arg);
        return F_JUMP_;
    } else if (my_strcomp(s, "JNZ") || my_strcomp(s, "CALL")) {
        *bul = 1;
        char arg_s[100];
        int i = 0;
        while(fgetc(code) != ':');
        while((arg_s[i] = fgetc(code)) != '\n') i+=1;
        ungetc(arg_s[i],code);
        arg_s[i] = '\0'; i = 0;
        while(i < label_list.counter && !my_strcomp(label_list.labels[i], arg_s)) i+=1;
        if (i == label_list.counter) return NO_CMD_;
        *arg = i;
        if (s[0] == 'J') {
            return F_JNZ_;
        } else {
            return F_CALL_;
        }
    } else {
        //=================================================
        // Is this a label?
        int len = 0;
        while (s[len]) len+=1;   // len = strlen(s);
        if (s[len-1] == ':') {
            //=============================================
            // We will call this label by number
            *bul = 1;
            *arg = label_list.curlbl;
            label_list.curlbl += 1;
            return F_LABEL_;
        } else {
            return NO_CMD_;
        }
    }
}

//=========================================================
// comparing strings
int my_strcomp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i += 1;
    }
    return 1;
}
