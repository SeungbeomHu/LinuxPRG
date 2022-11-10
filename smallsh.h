

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#define EOL 1
#define ARG 2
#define AMPERSAND 3
#define SEMICOLON 4
#define MAXARG          4096
#define MAXBUF          4096
#define FOREGROUND      0
#define BACKGROUND      1

#ifndef _SMALLSH_H_
#define _SMALLSH_H_

int userin(char* p);
void procline();
int gettok(char** outptr);
int inarg(char c);
char inpbuf[MAXBUF];
char tokbuf[2*MAXBUF];
char *ptr ;
char *tok ;
char *prompt;

#endif
