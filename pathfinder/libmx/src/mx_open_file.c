#include <libmx.h>

int mx_open_file(const char *file) {
    int x = open(file, 0);
    if(x < 0) {
        return -1;
    }
    return x;
}
