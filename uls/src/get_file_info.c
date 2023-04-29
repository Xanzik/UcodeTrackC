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

char* get_linked_file(t_file *file) {
    int size = file->info.st_size;
    char *res = mx_strnew(size);
    int link = readlink(file->path, res, size);
    if(link == -1) {
        mx_strdel(&res);
        return NULL;
    }
    res[link] = '\0';
    return res;
}

char get_extra_perms(t_file *file) {
    ssize_t buf = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW);
    acl_t acl = acl_get_file(file->path, ACL_TYPE_EXTENDED);
    if(buf > 0) {
        return '@';
    } else if(acl != NULL) {
        acl_free(acl);
        return '+';
    }
    return ' ';
}
