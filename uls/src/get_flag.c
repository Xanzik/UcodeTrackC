#include "../inc/uls.h"

t_flag* get_flags(int argc, char **argv) {
    t_flag* flags = malloc(sizeof(t_flag));
    flags->count = 0;
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1) {
            for(int j = 1; argv[i][j] != '\0'; j++) {
                if(is_flag(argv[i][j])) {
                    add_flag(&flags, argv[i][j]);
                }
            }
        }
    }
    return flags;
}

void add_flag(t_flag** flags, char flag) {
    switch(flag) {
        case 'l':
            (*flags)->l = 1;
            (*flags)->count++;
            break;
        default:
            break;
    }
}

bool is_flag(char flag) {
    for(int i = 0; i < 1; i++) {
        if(flag == FLAGS[i]) {
            return true;
        }       
    }
    return false;
}
