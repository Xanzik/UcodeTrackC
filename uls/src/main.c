#include "../inc/uls.h"

int main(int argc, char **argv) {
    if(argc == 1) {
        uls_without_flags();
    }
    if (argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
        printl();
    }
    if(argc != 1) {
         uls_directory_search(argc, argv);
    }
    return 0;
}
