#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "commands.h"
#define LBL_MAX_LEN_ 20
struct lbls {
    char *labels[100];
    int counter;
    int curlbl;
} label_list = {0};

int fill_lbl(FILE *);
int strcomp(const char *, const char *);
int find_cmd(char *, int *, int *, FILE *);

int main () {
    FILE *code, *recode;
    code = fopen("Prog.txt", "r"); assert(code);
    recode = fopen("Prog.ap", "w"); assert(recode);
    fill_lbl(code);
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
            ungetc(c, code);
        } else {
            //=============================================
            // writing assembled code
            fprintf(recode, "%d", cmd_code);
            fprintf(stdout, "%d", cmd_code);
            if (isarg) {
                fprintf(recode, " %d", arg);
                fprintf(stdout, " %d", arg);
            }
            fprintf(recode, "\n");
            fprintf(stdout, "\n");
            if (cmd_code == F_END_) break;
        }
    } while (fgetc(code) != EOF && cmd_code != F_END_);
    fclose(code); getchar();
    fclose(recode);
    if (errflag) {
        system("del Prog.ap");
        return -1;
    }
    return 0;
}

//=========================================================
// Fills the (label_list)
int fill_lbl(FILE *code) {
    while (!feof(code)) {
        int str[LBL_MAX_LEN_];
        //=================================================
        // Is this a label?
        int len = 0;
        while ((str[len] = fgetc(code)) != '\n' && str[len]!=EOF) {
            fprintf(stderr,"%c",str[len]);
            len+=1;   // len = strlen(str);
        }
        if (str[len-1] == ':') {
            label_list.labels[label_list.counter] = (char *)calloc(len, sizeof(char));
            int j = 0;
            for (j = 0; j < len; j++) label_list.labels[label_list.counter][j] = str[j];
            label_list.labels[label_list.counter][len-1] = '\0';
            fprintf(stderr, "[ LBL ] %s\n",label_list.labels[label_list.counter]);
            label_list.counter += 1;
        }
    }
    label_list.curlbl = 0;
    rewind(code);
    return 0;
}

//=========================================================
// returns code of command
int find_cmd(char s[], int *bul, int *arg, FILE *code) {
    // is command needs an argument?
    *bul = 0;
    fprintf(stderr, "[ N E ] %s\n", s);
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
    } else if (strcomp(s, "RET")) {
        return F_RET_;
    } else if (strcomp(s, "HALT")) {
        return F_HALT_;
    } else if (strcomp(s, "CMP")) {
        return F_CMP_;
    } else if (strcomp(s, "JUMP")) {
        *bul = 1;
        fscanf(code, "%d", arg);
        return F_JUMP_;
    } else if (strcomp(s, "JNZ") || strcomp(s, "CALL")) {
        *bul = 1;
        char arg_s[100];
        int i = 0;
        while(fgetc(code) != ':');
        while((arg_s[i] = fgetc(code)) != '\n') i+=1;
        arg_s[i] = '\0'; i = 0;
        while(i < label_list.counter && !strcomp(label_list.labels[i], arg_s)) i+=1;
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
        int i = 0;
        while (s[i]) i+=1;   // i = strlen(s);
        if (s[i-1] == ':') {
            *bul = 1;
            //=============================================
            // We will call this label by number
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
int strcomp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i += 1;
    }
    return 1;
}
