#include "smallsh.h"

int gettok(char** outptr) {
    int type;
    *outptr = tok;
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    *tok++ = *ptr;
    switch (*ptr++) {
        case '\n':
            type = EOL;
            break;
        case '&':
            type = AMPERSAND;
            break;
        case ';':
            type = SEMICOLON;
            break;
        default:
            type = ARG;
            while (inarg(*ptr))
                *tok++ = *ptr++;
    }
    *tok++ = '\0';
    return type;
}