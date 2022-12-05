#include "libmx.h"

bool mx_isletter(char s) {
    if(s >= 'A' && s <= 'Z')
        return s+('a'-'A');
    return s;
}
