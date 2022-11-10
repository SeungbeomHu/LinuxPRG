#include "smallsh.h"

int userin(char *p){
    int c,count;
    ptr = inpbuf;
    tok = tokbuf;

    printf("%s > ",p);

    count = 0;

    while (1){

        if ((c = getchar()) == EOF){
            return EOF;
        }
        if (count < MAXBUF) {
            inpbuf[count++] = c;
        }
        if (c == '\n' && count < MAXBUF) {
            inpbuf[count] = '\0';
            return count;
        }
        if (c == '\n' || count >= MAXBUF) {
        printf("smallsh: input line too long\n");
        count = 0;
        printf("%s", p);
    }
    }

}
