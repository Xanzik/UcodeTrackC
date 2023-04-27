#include "../inc/uls.h"

void uls_directory_search(int argc, char **argv) {
    int is_terminal;
    is_terminal = isatty(STDOUT_FILENO);
    int file_count = 0;
    int directory_count = 0;
    t_file *files_head = NULL;
    t_file *dirs_head = NULL;
    int file_index = 0;
    int dir_index = 0;

    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) != -1) {
            struct stat st;
            if (stat(argv[i], &st) == 0 && S_ISREG(st.st_mode)) {
                file_count++;
                add_file(&files_head, argv[i], file_index);
                file_index++;
            }
            else {
                directory_count++;
                add_file(&dirs_head, argv[i], dir_index);
                dir_index++;
            }
        }
    }

    print_files(files_head, is_terminal);

    if(directory_count != 0 && file_count > 0) {
        mx_printstr("\n");
    }
    print_directories(dirs_head, is_terminal, file_count, directory_count);

    free_files(files_head);
    free_files(dirs_head);
}
