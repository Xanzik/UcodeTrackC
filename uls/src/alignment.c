#include "../inc/uls.h"

int get_lenght(t_file *head) {
    int max_lenght = 0;
    t_file *current = head;
    while(current != NULL) {
        int len = mx_strlen(current->name);
        if(len > max_lenght) {
            max_lenght = len;
        }
        current = current->next;
    }
    free_files(current);
    return max_lenght;
}

int get_num_tabs(int width, int len) {
    int dif = width - len;
    if(dif % 8 != 0) {
        return dif / 8 + 1;
    }
    else {
        return dif / 8;
    }
}

void mx_print_tab(int width, int len) {
    int count_tabs = get_num_tabs(width, len);
    for(int i = 0; i < count_tabs; i++) {
        mx_printstr("\t");
    }
}

int get_col_width(int max_lenght) {
    if(max_lenght % 8 == 0) {
        max_lenght += 8;
    }
    else {
        max_lenght += 8 - (max_lenght % 8);
    }
    return max_lenght;
}

int get_cols(int w_cols, int width) {
    int col = 0;
    if(w_cols / width != 0) {
        col = w_cols / width;
    }
    if(width*col > w_cols 
        && col != 1) {
            col--;
        }
    return col;
}

int get_rows(int col, int count) {
    int row = count / col;
    if(row == 0
        || count % col != 0) {
            row++;
        }
    return row;
}
