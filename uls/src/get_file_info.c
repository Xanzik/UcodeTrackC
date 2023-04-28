#include "../inc/uls.h"

char *get_permissions(struct stat *info) {
    mode_t mode = info->st_mode;
    char *permissions = mx_strnew(10);
    int i = 0;
    permissions[i++] = *(IS_DIR(mode));
    permissions[i++] = *(IS_RUSR(mode));
    permissions[i++] = *(IS_WUSR(mode));
    permissions[i++] = *(IS_XUSR(mode));
    permissions[i++] = *(IS_RGRP(mode));
    permissions[i++] = *(IS_WGRP(mode));
    permissions[i++] = *(IS_XGRP(mode));
    permissions[i++] = *(IS_ROTH(mode));
    permissions[i++] = *(IS_WOTH(mode));
    permissions[i++] = *(IS_XOTH(mode));
    return permissions;
}

void get_lm_date(t_file **file, struct stat *info) {
    time_t cur_time;
    time(&cur_time);
    char *time_str = mx_strnew(100);
    mx_strcpy(time_str, ctime(&info->st_mtime));
    char **lm = mx_strsplit(time_str, ' ');
    (*file)->lm_month = mx_strdup(lm[1]);
    (*file)->lm_day = mx_strdup(lm[2]);
    int temp = cur_time - info->st_mtime;
    if(temp > 15552000|| (temp < 0 && temp > (-1 * 15552000))) {
        (*file)->lm_time = mx_strndup(lm[4], 4);
    }
    else {
        (*file)->lm_time = mx_strndup(lm[3], 5);
    }
    free(time_str);
    mx_del_strarr(&lm);
}
