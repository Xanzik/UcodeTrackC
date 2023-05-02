#include "../inc/uls.h"

void uls_without_flags(t_flag *flags) {
    int is_terminal = isatty(STDOUT_FILENO);
    t_file *head = NULL;
    full_list(&head, flags, NULL);
    sort_files(&head, flags);
    print_files(head, is_terminal, flags);
    free_files(head);
}
