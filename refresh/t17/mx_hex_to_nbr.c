#include <stdlib.h>
#include <stdbool.h>

bool mx_isalpha(int c) {
	if ((c >= 65 
	     && c <= 90) 
	     || (c >= 97 
	     && c <= 122)) {
		return true;
	}
	return false;
}

bool mx_isdigit(int c) {
    if (c >= 48
        && c <= 57) {
        return true;
    }
    return false;
}

bool mx_islower(int c) {
    if (c >= 97 
        && c <= 122) {
        return 1;
    }
    return 0;
}

bool mx_isupper(int c) {
    if (c >= 65 
        && c <= 90) {
        return 1;
    }
    return 0;
}

unsigned long mx_hex_to_nbr(const char *hex) {
    int len = 0;
    unsigned long num = 0;
    unsigned long base = 1;

    if (hex == NULL)
        return 0;

    if (hex != NULL) {
        while (hex[len])
            len++;
    }

    for (int i = 0; i <= len; i++) {
        if (mx_isdigit(hex[len - i])) {
            num += (hex[len - i] - 48) * base;
            base *= 16;
        }
        if (mx_isalpha(hex[len - i]) && mx_isupper(hex[len - i])) {
            num += (hex[len - i] - 55) * base;
            base *= 16;
        }
        if (mx_isalpha(hex[len - i]) && mx_islower(hex[len - i])) {
            num += (hex[len - i] - 87) * base;
            base *= 16;
        }
    }

    return num;
}
