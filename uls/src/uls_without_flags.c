#include "../inc/uls.h"

void uls_without_flags() {
    int is_terminal;
    is_terminal = isatty(STDOUT_FILENO);
    t_file *head = NULL;
    full_list(&head);
    sort_files(&head);
    print_files(head, is_terminal);
    free_files(head);
}
