#include "../inc/uls.h"

void print_files(t_file *head, int is_terminal) {
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
        sort_files(&current);
    max_lenght = get_lenght(head);
    width = get_col_width(max_lenght);
    cols = get_cols(w.ws_col, width);
    if(file_count * width > w.ws_col) {
        mult = 1;
    }
    if(is_terminal) {
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
            rows = get_rows(cols, file_count);
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j+i < file_count + 1; j += rows) {
                    current = get_index_file(head, i+j);
                    mx_printstr(current->name);
                    if(current->next && i+j+rows < file_count + 1) {
                        mx_print_tab(width, mx_strlen(current->name));
                    }
                }
                mx_printstr("\n");
            }
        }
    } else {
        int step = 0;
        while(step != file_count + 1) {
            mx_printstr(current->name);
            mx_printchar('\n');
            if(current->next != NULL)
                current = current->next;
            step++;
        }
    }
}
