#include "smallsh.h"

void sig_handler(int sig, siginfo_t *siginfo, void* param2){

				int status;
				waitpid(siginfo->si_pid,&status,WNOHANG);

				printf("[pid : %d] : 종료됨\n",siginfo->si_pid);
}


void setpromt(){
    char cwd[MAXARG] = "";

    getcwd(cwd,MAXARG);
    prompt = cwd;

    struct passwd* pw;
    pw = getpwuid(getuid());
    char* homdir = pw -> pw_dir;

    int homedirlen = strlen(homdir);
    int wdlen = strlen(prompt);

    if(wdlen>=homedirlen){
        int check = 1;
        for(int i=0;i<homedirlen;i++){
            if(prompt[i]!=homdir[i]){
                check = 0;
            }
        }

        if(check==1){

            if(homedirlen==wdlen){
                prompt="~";
            }
            else{
                char home[MAXARG+2]="~";
                char newpwd[MAXARG]="";
                strncpy(newpwd,cwd+homedirlen,wdlen-homedirlen);
                strcat(home,newpwd);
                prompt = home;
            }
        }
    }
}


int main() {

				pid_t pid;
				act.sa_sigaction = sig_handler;
				//act.sa_flags = SA_SIGINFO|SA_RESTART|SA_NOCLDWAIT;
				act.sa_flags = SA_SIGINFO|SA_RESTART;
				sigaction(SIGCHLD,&act,0);


    setpromt();
    while(userin(prompt) != EOF) {
        procline();
        setpromt();
    }
    return 0;
}

