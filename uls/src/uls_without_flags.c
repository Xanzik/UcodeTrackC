#include "../inc/uls.h"

void uls_without_flags() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int is_terminal;
    struct dirent *entry;
    DIR *dir;
    is_terminal = isatty(STDOUT_FILENO);
    dir = opendir(".");
    t_file *head = NULL;
    int max_filename_len = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") == 0 
            || mx_strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.') {
                continue;
        }
        char *path = entry->d_name;
        add_file(&head, path);
        int len = mx_strlen(entry->d_name);
        if (len > max_filename_len)
            max_filename_len = len;
    }
    closedir(dir);
    sort_files(&head);
    t_file *current = head;
    int terminal_cols = w.ws_col;
    int cols_count = terminal_cols / (max_filename_len + 1);
    int row = 0;
    while (current != NULL) {
        if (is_terminal) {
            if (row == cols_count) {
                mx_printstr("\n");
                row = 0;
            }
            int padding = max_filename_len - mx_strlen(current->name) + 1;
            mx_printstr(current->name);
            for (int i = 0; i < padding; ++i)
                mx_printchar(' ');
            ++row;
        }
        else {
            mx_printstr(current->name);
            mx_printstr("\n");
        }
        current = current->next;
    }
    free_files(head);
    free_files(current);
}
