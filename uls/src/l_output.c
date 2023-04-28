#include "../inc/uls.h"

void printl() {
    DIR *dir;
    struct dirent *entry;
    t_file *head = NULL;
    int total_blocks = 0;
    int index = 0;
    dir = opendir(".");
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") == 0
            || mx_strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.') {
                continue;
        }
        char *path = entry->d_name;
        add_file_l(&head, path, index);
        index++;
        if(stat(entry->d_name, &head->info) != -1) {
            total_blocks += head->info.st_blocks;
        }
    }
    int count = get_file_count(head);
    t_file *current = head;
    if(count > 0)
        sort_files(&current);
    mx_printstr("total ");
    mx_printint(total_blocks);
    mx_printchar('\n');
    while(current != NULL) {
        if (lstat(current->name, &head->info) != -1) {
            printFileInfo(&head->info, current);
        }
        current = current->next;
    }
    closedir(dir);
}

void printFileInfo(struct stat *info, t_file *filename) {
    mx_printstr(filename->perms);
    mx_printstr("  ");
    mx_printstr(filename->num_links);
    mx_printstr(" ");
    mx_printstr(filename->user_name);
    mx_printstr("  ");
    mx_printstr(filename->group_name);
    mx_printstr("  ");
    mx_printint(info->st_size);
    mx_printstr(" ");
    mx_printstr(filename->lm_month);
    mx_printstr(" ");
    mx_printstr(filename->lm_day);
    mx_printstr(" ");
    mx_printstr(filename->lm_time);
    mx_printstr(" ");
    mx_printstr(filename->name);
    mx_printchar('\n');
}
