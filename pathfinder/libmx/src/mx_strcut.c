#include "libmx.h"

char *mx_strcut(const char *s, char c) {
    int count = 0;
    if (!s) {
        return NULL;
    }
    count = CountLetters(s, c);
    char *arr = mx_strndup(s, count);
    return arr;
}
