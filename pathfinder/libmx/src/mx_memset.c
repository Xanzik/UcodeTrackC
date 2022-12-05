#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *ptr = (char *)b;
    while (len > 0) {
        *ptr++ = (char)c;
        len--;
   }
  return ptr;
}
