#include "../inc/uls.h"

void print_files(t_file *head, int is_terminal, t_flag *flags) {
    int file_count;
    int width;
    int max_lenght;
    int cols;
    int rows;
    t_file *current = head;
    int mult = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    file_count = get_file_count(head);
    if(file_count != 1)
        sort_files(&current, flags);
    max_lenght = get_lenght(head);
    width = get_col_width(max_lenght);
    cols = get_cols(w.ws_col, width);
    if(file_count * width > w.ws_col) {
        mult = 1;
    }
    if((!is_terminal || flags->one) && flags->C != 1) {
        int step = 0;
        while(step != file_count + 1) {
            mx_printstr(current->name);
            mx_printchar('\n');
            if(current->next != NULL)
                current = current->next;
            step++;
        }
    } else if(is_terminal) {
        if(mult != 1) {
            current = head;
            while (current != NULL) {
                mx_printstr(current->name);
                if(current->next != NULL) {
                    mx_print_tab(width, mx_strlen(current->name));
                }
                current = current->next;
            }
            mx_printchar('\n');
        }
        else {
            rows = get_rows(cols, file_count+1);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j+i < file_count+1; j += rows) {
                    current = get_index_file(head, i+j);
                    mx_printstr(current->name);
                    if(current->next && i+j+rows < file_count+1) {
                        mx_print_tab(width, mx_strlen(current->name));
                    }
                }
                mx_printstr("\n");
            }
        }
    }
}

void print_directories(t_file *head, int is_terminal, int file_count, int directory_count, t_flag *flags) {
    DIR *dir;
    struct dirent *de;
    t_file *current = head;
    if(file_count > 1)
        sort_files(&current, flags);
    int step = 0;
    while (current != NULL) {
        if(((directory_count != 1 || file_count > 0) || (directory_count == 1 && flags->error == 1))
            && flags->R != 1) {
            mx_printstr(current->name);
            mx_printstr(":\n");
        } else if(flags->R == 1) {
            mx_printstr("./");
            mx_printstr(current->name);
            mx_printstr(":\n");
        }
        dir = opendir(current->name);
        // Create a list of files for this directory
        t_file *dir_files = NULL;
        int index = 0;
        while ((de = readdir(dir)) != NULL) {
            if(mx_strcmp(de->d_name, ".") == 0 
                || mx_strcmp(de->d_name, "..") == 0
                || de->d_name[0] == '.'){
                continue;
            }
            if(flags->R == 1)
                add_file(&dir_files, de->d_name, index, flags, current->name);
            if(flags->R != 1)
                add_file(&dir_files, de->d_name, index, flags, NULL);
            index++;
        }
        // Sort the files in this directory
        sort_files(&dir_files, flags);
        // Print the files in this directory
        if(index > 0 && flags->l != 1)
            print_files(dir_files, is_terminal, flags);
        if(index > 0 && flags->l == 1 && flags->R == 1) {
            dir = opendir(current->path);
            print_current_l(flags, dir, current->path);
        }
        // Free the list of files for this directory
        free_files(dir_files);
        if(flags->R) {
            dir = opendir(current->name);
                mx_printchar('\n');
            print_R(flags, dir, current->name, 0, 0, 0);
            
        }
        step++;
        if (!is_terminal) {
            if(step != directory_count)
                mx_printstr("\n");
            }
        else {
            if(step != directory_count && flags->R != 1) {
                mx_printstr("\n");
            }
        }
        current = current->next;
    }
}
