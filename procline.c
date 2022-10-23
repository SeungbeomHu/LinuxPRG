#include "smallsh.h"

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
                break;

            case SEMICOLON:
                break;

            case AMPERSAND:
                if (toktype == AMPERSAND){
                    type = BACKGROUND;
                }
                else{
                    type = FOREGROUND;
                }
                if (narg != 0){
                    arg[narg] = NULL;
                    runcommand(arg,type);
                }
                if (toktype == EOL){
                    return;
                }
                narg = 0;
                break;

        }
    }
}