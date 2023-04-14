#include "libmx.h"

char *mx_strtok(char *str, const char *delim) {
    static char *last = NULL;
    if (str != NULL)
        last = str;

    if (last == NULL)
        return NULL;

    char *start = last;
    char *delim_pos;
    while (*last != '\0') {
        delim_pos = (char*) delim;
        while (*delim_pos != '\0') {
            if (*last == *delim_pos) {
                *last = '\0';
                last++;
                if (start == last)
                    start++;
                return start;
            }
            delim_pos++;
        }
        last++;
    }
    return NULL;
}
