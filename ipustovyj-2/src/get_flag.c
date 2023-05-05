#include "../inc/uls.h"

t_flag* get_flags(int argc, char **argv) {
    t_flag* flags = malloc(sizeof(t_flag));
    flags->error = 0;
    flags->count = 0;
    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1) {
            for(int j = 1; argv[i][j] != '\0'; j++) {
                if(is_flag(argv[i][j])) {
                    add_flag(&flags, argv[i][j]);
                }
                else {
                    mx_printerr("uls: ");
                    mx_printerr("illegal option -- ");
                    mx_printerr(&argv[i][j]);
                    mx_printerr("\n");
                    mx_printerr("usage : uls [-lRC1AaGeT@rtucS] [file ...]\n");
                    exit(1);
                }
            }
        } else {
            break;
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
        case 'R':
            (*flags)->R = 1;
            (*flags)->count++;
            break;
        case 'C':
            (*flags)->C = 1;
            (*flags)->one = 0;
            (*flags)->count++;
            break;
        case '1':
            (*flags)->one = 1;
            (*flags)->C = 0;
            (*flags)->count++;
            break;
        case 'A':
            (*flags)->A = 1;
            (*flags)->count++;
            break;
        case 'a':
            (*flags)->a = 1;
            (*flags)->count++;
            break;
        case 'G':
            (*flags)->G = 1;
            (*flags)->count++;
            break;
        case 'e':
            (*flags)->e = 1;
            (*flags)->count++;
            break;
        case 'T':
            (*flags)->T = 1;
            (*flags)->count++;
            break;
        case '@':
            (*flags)->at = 1;
            (*flags)->count++;
            break;
        case 'r':
            (*flags)->r = 1;
            (*flags)->count++;
            break;
        case 'u':
            (*flags)->u = 1;
            (*flags)->c = 0;
            (*flags)->count++;
            break;
        case 'c':
            (*flags)->c = 1;
            (*flags)->u = 0;
            (*flags)->count++;
            break;
        case 'S':
            (*flags)->S = 1;
            (*flags)->count++;
            break;
        case 't':
            (*flags)->t = 1;
            (*flags)->count++;
            break;
        default:
            break;
    }
}

bool is_flag(char flag) {
    for(int i = 0; i < 16; i++) {
        if(flag == FLAGS[i]) {
            return true;
        }       
    }
    return false;
}

bool check_dir(char **argv, int argc) {
    for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1) {
    } else {
        return 1;
    }
    }
    return 0;
}
