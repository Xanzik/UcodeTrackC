#include "../inc/uls.h"

void printl(t_flag *flags, int argc, char **argv) {
    if(argc == 2) {
        print_current_l(flags, NULL, NULL);
    }
    else {
        print_all_l(argv, flags, argc);
    }
}

void printFileInfo(t_file *filename, t_flag *flags) {
    mx_printstr(filename->perms);
    mx_printchar(get_extra_perms(filename));
    mx_printstr(" ");
    mx_printstr(filename->num_links);
    mx_printstr(" ");
    mx_printstr(filename->user_name);
    mx_printstr("  ");
    mx_printstr(filename->group_name);
    mx_printstr("  ");
    mx_printstr(filename->size);
    mx_printstr(" ");
    mx_printstr(filename->lm_month);
    mx_printstr(" ");
    mx_printstr(filename->lm_day);
    mx_printstr(" ");
    mx_printstr(filename->lm_time);
    mx_printstr(" ");
    mx_printstr(filename->name);
    if(filename->linked_file) {
        mx_printstr(" -> ");
        mx_printstr(filename->linked_file);
    }
    mx_printchar('\n');
    if(flags->at && listxattr(filename->path, NULL, 0, XATTR_NOFOLLOW) > 0) {
        output_xattr(filename->path);
    }
    if(flags->e && filename->acl_str != NULL) {
        output_acl(filename->acl_str);
    }
}

void print_current_l(t_flag *flags, DIR *dir, char *half) {
    if(dir == NULL)
        dir = opendir(".");
    struct dirent *entry;
    t_file *head = NULL;
    int index = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") == 0
            || mx_strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.') {
                continue;
        }
        char *path = entry->d_name;
        if(flags->R == 1) {
            if(half != NULL)
                path = get_path_dir(half, entry->d_name);
            add_file(&head, entry->d_name, index, flags, path);
            index++;
        } else {
        add_file(&head, path, index, flags, NULL);
        index++;
        }
    }
    int count = 0;
    if(head != NULL)
        count = get_file_count(head);
    t_file *current = head;
    if(count > 0)
        sort_files(&current, flags);
    info_lenght(&current);
    mx_printstr("total ");
    int total = 0;
    total = total_block(&current);
    mx_printint(total);
    mx_printchar('\n');
    while(current != NULL) {
        if (lstat(current->path, &head->info) != -1) {
            printFileInfo(current, flags);
        }
        current = current->next;
    }
}

void print_all_l(char **argv, t_flag *flags, int argc) {
    t_file *files_head = NULL;
    t_file *dirs_head = NULL;
    int file_index = 0;
    int dir_index = 0;
    int file_count = 0;
    int directory_count = 0;
    int num_words = argc-1;
    char **list = (char **)malloc(num_words * sizeof(char *));
    for(int i = 0; i < num_words; i++) {
        list[i] = (char *)malloc((mx_strlen(argv[i+1]) + 100) * sizeof(char));
    }
    int check = 0;
    for (int i = 2; i < argc; i++) {
        struct stat st;
        if (lstat(argv[i], &st) == 0) {

            if (stat(argv[i], &st) == 0 && S_ISREG(st.st_mode)) {
                file_count++;
                add_file(&files_head, argv[i], file_index, flags, NULL);
                file_index++;
            }
            else {
                directory_count++;
                add_file(&dirs_head, argv[i], dir_index, flags, NULL);
                dir_index++;
            }
        } else {
            if(argv[i][0] == '-' && mx_strlen(argv[i]) > 1 && dir_index == 0) {

            } else {
            mx_strcpy(list[check], argv[i]);
            flags->error = 1;
            check++;
            }
        }
    }
    if(flags->error == 1) {
        sort_err(list, check);
        for(int i = 0; i < check; i++) {
            if(list[i] != NULL)
                print_dir_err(strerror(errno), list[i]);
        }
    }
    if(file_count != 0) {
        sort_files(&files_head, flags);
        info_lenght(&files_head);
        while(files_head != NULL) {
        if (lstat(files_head->name, &files_head->info) != -1) {
            printFileInfo(files_head, flags);
        }
        files_head = files_head->next;
        }
    }
    if(directory_count != 0 && file_count > 0) {
        mx_printchar('\n');
        sort_files(&dirs_head, flags);
    }
    print_dir_l(dirs_head, file_count, directory_count, flags);
}

void print_dir_l(t_file *head, int file_count, int directory_count, t_flag *flags) {
    DIR *dir;
    struct dirent *de;
    t_file *current = head;
    sort_files(&current, flags);
    while (current != NULL) {
        if(directory_count != 1 || file_count > 0 || flags->error == -1) {
            mx_printstr(current->name);
            mx_printstr(":\n");
        }
        int total_blocks = 0;
        mx_printstr("total ");
        dir = opendir(current->name);
        t_file *dir_files = NULL;
        int index = 0;
        while ((de = readdir(dir)) != NULL) {
            if(mx_strcmp(de->d_name, ".") == 0 
                || mx_strcmp(de->d_name, "..") == 0
                || de->d_name[0] == '.') {
                continue;
            }
            char *path = get_path_dir(current->name, de->d_name);
            add_file(&dir_files, de->d_name, index, flags, path);
            index++;
        }
        total_blocks = total_block(&dir_files);
        mx_printint(total_blocks);
        mx_printstr("\n");
        sort_files(&dir_files, flags);
        info_lenght(&dir_files);
        while(dir_files != NULL) {
            if (lstat(current->name, &dir_files->info) != -1) {
                printFileInfo(dir_files, flags);
            }
            dir_files = dir_files->next;
        }
        if(flags->R) {
            dir = opendir(current->name);
            //mx_printchar('\n');
            print_R(flags, dir, current->name, 0, 0, 0);
        }
        if(current->next != NULL)
            mx_printchar('\n');
        current = current->next;
    }
}

int total_block(t_file **files) {
    int total = 0;
    t_file *file = *files;
    while(file) {
        if(stat(file->path, &file->info) != -1)
            total += file->info.st_blocks;
        file = file->next;
    }
    return total;
}

void output_acl(const char* acl) {
    char **acl_l = mx_strsplit(acl, '\n');
    for(int i = 1; acl_l[i] != NULL; ++i) {
        char **params = mx_strsplit(acl_l[i], ':');
        acL_params(params, i-1);
        mx_del_strarr(&params);
    }
    mx_del_strarr(&acl_l);
}

void acL_params(char **params, int i) {
    mx_printchar(' ');
    mx_printint(i);
    mx_printstr(": ");
    mx_printstr(params[0]);
    mx_printstr(":");
    mx_printstr(params[2]);
    mx_printchar(' ');
    mx_printstr(params[4]);
    mx_printchar(' ');
    mx_printstr(params[5]);
    mx_printchar('\n');
}

void output_xattr(const char *path) {
    char namebuf[255];
    char tmp[255];
    int len = listxattr(path, namebuf, 255, XATTR_NOFOLLOW);
    int i = 0;
    int temp_len = 0;
    while(i < len) {
        mx_printchar('\t');
        mx_printstr(&namebuf[i]);
        temp_len = getxattr(path, &namebuf[i], tmp, 255, 0, 0);

        mx_printstr("\t   ");
        if(temp_len != -1) {
            mx_printint(temp_len);
        } else {
            mx_printint(0);
        }
        mx_printstr(" \n");
        i+= mx_strlen(&namebuf[i]) + 1;
    }
}
