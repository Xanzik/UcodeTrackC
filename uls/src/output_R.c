#include "../inc/uls.h"

void print_R(t_flag *flags, DIR *dir, char *path, bool first, bool end, int num) {
    int is_terminal = isatty(STDOUT_FILENO);
    int count = 0;
    if(dir == NULL || first == 1) {
        t_file *head = NULL;
        int d_count = 0;

        full_list(&head, flags, dir);
        sort_files(&head, flags);
        if(head)
            count = get_file_count(head);
        if(num > 1 || end != 1) {
            mx_printstr(path);
            mx_printstr(":\n");
        }
        if(flags->l != 1)
            print_files(head, is_terminal, flags);
        if(flags->l == 1) {
            print_current_l(flags, dir, path);
        }
        //free_files(head);
        t_file *direct = NULL;
        full_list_dir(&direct, flags, dir, path);
        if(direct != NULL) {
            sort_files(&direct, flags);
            d_count = get_file_count(direct);
        }
        if(d_count != 0) {
            mx_printchar('\n');
            if(flags->l != 1)
                print_directories(direct, is_terminal, count, d_count, flags);
            if(flags->l == 1) {
                print_dir_l(direct, count, d_count, flags);
            }
        }
        if(end != 1 && !flags->l) {
            mx_printchar('\n');
        }
    } else {
        t_file *direct = NULL;
        full_list_dir(&direct, flags, dir, path);
        int d_count = 0;
        if(direct != NULL) {
            d_count = get_file_count(direct);
            sort_files(&direct, flags);
        }
        if(d_count != 0) {
            print_directories(direct, is_terminal, count, d_count, flags);
        }
    }
}

void output_R_dir(int argc, char **argv, t_flag *flags) {
        if(argc > 2) {
        int num_words = argc - 1;
        char **list = (char **)malloc(num_words * sizeof(char *));
        for(int i = 0; i < num_words; i++) {
            list[i] = (char *)malloc((mx_strlen(argv[i+1]) + 100) * sizeof(char));
        }
        t_file *files = NULL;
        int file_index = 0;
        int dier = 0;
        if(argc > flags->count) {
            for (int i = 1; i < argc; i++) {
                struct stat st;
                if (lstat(argv[i], &st) == 0) {
                    if (stat(argv[i], &st) == 0 && S_ISREG(st.st_mode)) {
                        add_file(&files, argv[i], file_index, flags, NULL);
                        file_index++;
                    }
                    else {
                    if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1 && file_index == 0) {

                    } else {
                        mx_strcpy(list[dier], argv[i]);
                        dier++;
                    }
                    }
                }
            }
            sort_files(&files, flags);
        }
        if(files) {
            if(flags->l) {
                info_lenght(&files);
                while(files != NULL) {
                if (lstat(files->name, &files->info) != -1) {
                    printFileInfo(files, flags);
                    if(dier != 0)
                        mx_printchar('\n');
                }
                files = files->next;
                }    
            }
            if(flags->R && flags->l != 1) {
                print_files(files, isatty(1), flags);
            }
        }
        if(dier > 1)
            sort_err(list, dier);
        int end = 0;
        int first = 1;
        for(int i = 0; i < dier; i++) {
            if(i+1 == dier) {
                end = 1;
            }
            DIR *dir = opendir(list[i]);
            print_R(flags, dir, list[i], first, end, dier);
        }
        for(int i = 0; i < dier; i++) {
        free(list[i]);
        }
        free(list);
    } else {
        print_R(flags, NULL, NULL, 0, 1, 0);
    }
}
