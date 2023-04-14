#include "../inc/uls.h"


void printl() {
    DIR *dir;
    struct dirent *entry;
    t_file *head = NULL;
    struct stat info;
    int total_blocks = 0;
    dir = opendir(".");
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") == 0 
            || mx_strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.') {
                continue;
        }
        char *path = entry->d_name;
        add_file(&head, path);
        if(stat(entry->d_name, &info) != -1) {
            total_blocks += info.st_blocks;
        }
    }
    sort_files(&head);
    mx_printstr("total ");
    mx_printint(total_blocks/2);
    mx_printchar('\n');
    while(head != NULL) {
        if (stat(head->name, &info) != -1) {
            printFileInfo(&info, head->name);
        }
        head = head->next;
    }
    closedir(dir);
}

void printFileInfo(struct stat *info, char *filename) {
    struct passwd *pw = getpwuid(info->st_uid);
    struct group *gr = getgrgid(info->st_gid);
    char *ntime = mx_strnew(100);
    char *ntime_full = mx_strnew(20);
    mx_strcpy(ntime, ctime(&info->st_mtime));
    ntime_full = mx_strncpy(ntime_full, ntime + 4, 12);

    printPermissions(info->st_mode);
    mx_printstr(" ");
    mx_printint(info->st_nlink);
    mx_printstr(" ");
    mx_printstr(pw->pw_name);
    mx_printstr(" ");
    mx_printstr(gr->gr_name);
    mx_printstr(" ");
    mx_printint(info->st_size);
    mx_printstr(" ");
    mx_printstr(ntime_full);
    mx_printstr(" ");
    mx_printstr(filename);
    mx_printchar('\n');

    free(ntime_full);
    free(ntime);
}

void printPermissions(mode_t mode) {
    mx_printstr(IS_DIR(mode));
    mx_printstr(IS_RUSR(mode));
    mx_printstr(IS_WUSR(mode));
    mx_printstr(IS_XUSR(mode));
    mx_printstr(IS_RGRP(mode));
    mx_printstr(IS_WGRP(mode));
    mx_printstr(IS_XGRP(mode));
    mx_printstr(IS_ROTH(mode));
    mx_printstr(IS_WOTH(mode));
    mx_printstr(IS_XOTH(mode));
}
