#include "smallsh.h"

int runcommand(char **cline,int where){
    pid_t pid;
    int status;
    int fd_new;
    int redirect = 0;
		int isPipe = 0;
		int pipe_idx = 0;

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
				else if(strcmp(cline[i],"|")==0){
				
								isPipe = 1;
								pipe_idx = i;
								cline[i] = NULL;
								break;
				}
    }

		if(where==FOREGROUND){
					sigaction(SIGCHLD,&oldact,&act);
					sigprocmask(SIG_BLOCK,&signalset,NULL);
		}
    switch (pid = fork()) {
        case -1:
            perror("smallsh");
            return -1;
        case 0:
						if(where==FOREGROUND){
								sigprocmask(SIG_UNBLOCK,&signalset,NULL);
								sigaction(SIGINT,&oldact,&act);
								}
						else{
						sigprocmask(SIG_BLOCK,&signalset,NULL);			
						}


            if(redirect == 1){
                if(dup2(fd_new, 1) == -1)
                    perror("output redirection failed");
            }
						if(isPipe == 1){

										int pipe_fd[2];
										if(pipe(pipe_fd) == -1){
										perror("pipe error:");
										}

										switch(pid = fork()){
										
														case 0:
																		dup2(pipe_fd[1],1);
																		close(pipe_fd[0]);
																		close(pipe_fd[1]);
																		execvp(cline[0],&cline[0]);
														default:
																		dup2(pipe_fd[0],0);
																		close(pipe_fd[0]);
																		close(pipe_fd[1]);
																		execvp(cline[pipe_idx + 1],&cline[pipe_idx + 1]);
										}
						
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
				perror("error:");
        return -1;
    }
    else{
					sigprocmask(SIG_UNBLOCK,&signalset,NULL);	
					sigaction(SIGCHLD,&act,&oldact);
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
