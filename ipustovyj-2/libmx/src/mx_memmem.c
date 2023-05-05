#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {

	unsigned char *where = (unsigned char *)big;
	unsigned char *what = (unsigned char *)little;

	if (big_len >= little_len && big_len > 0 && little_len > 0) {
		while (*where++) {
			if (mx_memcmp(where, what, little_len - 1) == 0) {
				return where;
			}
		}
	}
	
	return NULL;
}
