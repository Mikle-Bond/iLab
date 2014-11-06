#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
struct lbls {
    char *labels[100];
    int counter;
} label_list = {0};

int main () {
    FILE *code, *recode;
    code = fopen("Prog.txt", "r");
    recode = fopen("Prog.ap", "w");
    char cmd_txt[5] = {'\0'};
    int cmd_code = 0;
    int strnom = 0, errflag = 0;
    int isarg = 0, arg = 0;
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
        cmd_code = find_cmd(cmd_txt, &isarg, &arg, code);
        if (cmd_code == NO_CMD_) {
            //=============================================
            // logging errors
            fprintf(stderr, "%d: command not recognized: %s\n", strnom, cmd_txt);
            errflag = 1;
            char c = 0;
            do c = fgetc(code); while (c != '\n');
            ungetwc(c, code);
        } else {
            //=============================================
            // writing assembled code
            fprintf(recode, "%d", cmd_code);
            if (isarg) {
                fprintf(recode, " %d", arg);
            }
            fprintf(recode, "\n");
        }
    } while (fgetc(code) != EOF && cmd_code != F_END_);
    fclose(code);
    fclose(recode);
    if (errflag) {
        system("del Prog.ap");
        return -1;
    }
    return 0;
}

//=========================================================
// returns code of command
int find_cmd(char s[], int *bul, int *arg, FILE *code) {
    // is command needs an argument?
    *bul = 0;
    /// fprintf(stderr, "[ N E ] %s\n", s);
    if (strcomp(s, "PUSH")) {
        *bul = 1;
        fscanf(code, "%d", arg);
        return F_PUSH_;
    } else if (strcomp(s, "ADD")) {
        return F_ADD_;
    } else if (strcomp(s, "MUL")) {
        return F_MUL_;
    } else if (strcomp(s, "OUT")) {
        return F_OUT_;
    } else if (strcomp(s, "END")) {
        return F_END_;
    } else if (strcomp(s, "CMP")) {
        return F_CMP_;
    } else if (strcomp(s, "JUMP")) {
        *bul = 1;
        fscanf(code, "%d", &arg);
        return F_JUMP_;
    } else if (strcomp(s, "JNZ")) {
        *bul = 1;
        char arg_s[100];
        int i = 0;
        while(fgetc(code) != ':');
        while((arg_s[i] = fgetc(code)) != '\n') i+=1;
        arg_s[i] = '\0'; i = 0;
        while(i < label_list.counter && !strcomp(label_list.labels[i], arg_s)) i+=1;
        *arg = i;
        return F_JNZ_;
    } else {
        //=================================================
        // Is this a label?
        int i = 0;
        while (s[i]) i+=1;   // i = strlen(s);
        if (s[i-1] == ':') {
            *bul = 1;
            label_list.labels[label_list.counter] = calloc(i, sizeof(char));
            int j = 0;
            for (j = 0; j < i; j++) label_list.labels[label_list.counter][j] = s[j];
            label_list.labels[label_list.counter][i-1] = '\0';
            //=============================================
            // We will call this label by number
            *arg = label_list.counter;
            label_list.counter += 1;
            return F_LABEL_;
        } else {
            return NO_CMD_;
        }
    }
}

//=========================================================
// comparing strings
int strcomp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i += 1;
    }
    return 1;
}
