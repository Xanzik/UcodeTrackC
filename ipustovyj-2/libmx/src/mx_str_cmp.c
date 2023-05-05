#include "libmx.h"

int mx_cmp_str(const char *s1, const char *s2) {
    while (*s1 && *s2 && (*s1 == *s2 || (*s1 | 0x20) == (*s2 | 0x20))) {
        s1++;
        s2++;
    }
    return (*s1 | 0x20) - (*s2 | 0x20);
}
