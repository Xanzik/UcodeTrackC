#include "../inc/uls.h"

int main(int argc, char **argv) {
    t_flag *flags = get_flags(argc, argv);
    if(flags->count == 0 && argc == 1) {
        uls_without_flags(flags);
    }
    else if (flags->l == 1) {
        printl(flags, argc, argv);
    }
    else if(argc != 1 && flags->count == 0) {
         uls_directory_search(argc, argv, flags);
    }
    return 0;
}
