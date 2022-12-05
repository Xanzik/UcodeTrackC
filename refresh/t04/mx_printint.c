#include <unistd.h>

void mx_printchar(char c);

int mx_getlength(int buffer) {
    int length = 0;
    for (int i = 0; buffer > 0; i++) {
        buffer /= 10;
        length++;
    }
    return length;
}

void mx_printint(int n) {
    int length = 0;
    int buffer = 0;
    if (n == 0) {
        mx_printchar('0');
    }
    else if(n == -2147483648) {
        n = n + 1;
        n *= -1;
        mx_printchar('-');
        char num[10];
        for(int i = 9; i >= 0; i--) {
            buffer = n % 10;
            num[i] = buffer + 48;
            n /= 10;
        }
        num[9] = '8';
        for (int i = 0; i < 10; i++)
            mx_printchar(num[i]);
    }
    else if (n < 0) {
        n *= -1;
        mx_printchar('-');
    buffer = n;
    length = mx_getlength(buffer);
    char num[length];
    for (int i = length - 1; i >= 0; i--) {
        buffer = n % 10;
        num[i] = buffer + 48;
        n /= 10;
    }
    for (int i = 0; i < length; i++)
        mx_printchar(num[i]);
    }
    write(1, "\n", 1);
}
