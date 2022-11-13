#include "smallsh.h"

int runcommand(char **cline,int where){
    pid_t pid;
    int status;
    int fd_new;
    int redirect = 0;


    if(strcmp(*cline, "exit") == 0){
        printf("Bye~\n");
        exit(0);
    }

    // cd
    if(strcmp(*cline, "cd") == 0){
        if(cline[2] != NULL){
            printf("Usage: cd <dir>\n");
            return 0;
        }

        if(cline[1]==NULL){

            struct passwd* pw;
            pw = getpwuid(getuid());
            char* homdir = pw -> pw_dir;
            cline[1] = homdir;
        }

        if(strcmp(cline[1],"~") == 0){
            struct passwd* pw;
            pw = getpwuid(getuid());
            char* homdir = pw -> pw_dir;
            cline[1] = homdir;
        }

        if(cline[1][0]=='~'){
            struct passwd* pw;
            pw = getpwuid(getuid());
            char* homdir = pw -> pw_dir;

            char temp[MAXARG];
            strcpy(temp,homdir);
            strcat(temp,&cline[1][1]);

            cline[1] = temp;

        }

        if(chdir(cline[1]) == -1)
            perror(cline[1]);
        return 0;
    }

    // >
    for(int i = 0; cline[i]; i++){
        if(strcmp(cline[i], ">") == 0){
            if((fd_new = open(cline[i + 1], O_WRONLY | O_CREAT, 0755)) == -1){
                perror(cline[i + 1]);
                return -1;
            }

            redirect = 1;
            cline[i] = NULL;
            break;
        }
    }




    switch (pid = fork()) {
        case -1:
            perror("smallsh");
            return -1;
        case 0:

            if(redirect == 1){
                if(dup2(fd_new, 1) == -1)
                    perror("output redirection failed");
            }
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

void procline() {
    char *arg[MAXARG + 1];
    int toktype, type;
    int narg = 0;
    for (;;) {
        switch (toktype = gettok(&arg[narg])) {

            case ARG:
                if(narg < MAXARG){
                    narg++;
                }
                break;

            case EOL:
            case SEMICOLON:
            case AMPERSAND:
                if (toktype == AMPERSAND){
                    type = BACKGROUND;
                }
                else{
                    type = FOREGROUND;
                }
                if (narg != 0){
                    arg[narg] = NULL;
                    if((runcommand(arg,type))==-1){
                        exit(0);
                    }
                }
                if (toktype == EOL){
                    return;
                }
                narg = 0;
                break;
        }
    }
}