#include "smallsh.h"

int runcommand(char **cline,int where){
    pid_t pid;
    int status;

    switch (pid = fork()) {
        case -1:
            perror("smallsh");
            return -1;
        case 0:
            execvp(*cline,cline);
            perror(*cline);
            exit(1);
    }
    if(where == BACKGROUND){
        printf("[Process id] %d\n",pid);
        return 0;
    }
    if(waitpid(pid,&status,0) == -1){
        return -1;
    }
    else{
        return status;
    }
}