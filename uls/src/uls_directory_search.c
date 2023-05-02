#include "../inc/uls.h"

void uls_directory_search(int argc, char **argv, t_flag *flags) {
    int is_terminal;
    int file_count = 0;
    int directory_count = 0;
    t_file *files_head = NULL;
    t_file *dirs_head = NULL;
    int file_index = 0;
    int dir_index = 0;
    int num_words = argc-1;
    char **list = (char **)malloc(num_words * sizeof(char *));
    for(int i = 0; i < num_words; i++) {
        list[i] = (char *)malloc((mx_strlen(argv[i+1]) + 100) * sizeof(char));
    }
    int check = 0;
    is_terminal = isatty(STDOUT_FILENO);
    for (int i = 1; i < argc; i++) {
        if (access(argv[i], F_OK) != -1) {
            struct stat st;
            if (stat(argv[i], &st) == 0 && S_ISREG(st.st_mode)) {
                file_count++;
                add_file(&files_head, argv[i], file_index, flags, NULL);
                file_index++;
            }
            else {
                directory_count++;
                add_file(&dirs_head, argv[i], dir_index, flags, NULL);
                dir_index++;
            }
        } else {
            if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1) {

            }
            else {
                mx_strcpy(list[check], argv[i]);
                flags->error = 1;
                check++;
            }
        }
    }

    if(flags->error == 1) {
        sort_err(list, check);
        for(int i = 0; i < check; i++) {
            if(list[i] != NULL)
                print_dir_err(strerror(errno), list[i]);
        }
    }
    if(file_count != 0) {
        sort_files(&files_head, flags);
        print_files(files_head, is_terminal, flags);
    }
    if(directory_count != 0 && file_count > 0) {
        mx_printstr("\n");
    }
    if(directory_count > 1) {
        sort_files(&dirs_head, flags);
    }
    print_directories(dirs_head, is_terminal, file_count, directory_count, flags);
    for(int i = 0; i < num_words; i++) {
        free(list[i]);
    }
    free(list);
    free_files(files_head);
    free_files(dirs_head);
}
