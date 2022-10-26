#ifndef _SMALLSH_H_
#define _SMALLSH_H_
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
#define MAXARG          512
#define MAXBUF          512
#define FOREGROUND      0
#define BACKGROUND      1
int userin(char* p);
void procline();
int gettok(char** outptr);
int inarg(char c);
int runcommand(char **cline, int where);
static char inpbuf[MAXBUF];
static char tokbuf[2*MAXBUF];
static char *ptr = inpbuf;
static char *tok = tokbuf;
char *prompt;
#endif
