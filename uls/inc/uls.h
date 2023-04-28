#pragma once

#include "../libmx/inc/libmx.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define FLAGS "l"

typedef struct s_flag {
    int l;
    int count;
}               t_flag;

#define IS_DIR(mode) ((mode) & S_IFDIR ? "d" : "-")
#define IS_RUSR(mode) ((mode) & S_IRUSR ? "r" : "-")
#define IS_WUSR(mode) ((mode) & S_IWUSR ? "w" : "-")
#define IS_XUSR(mode) ((mode) & S_IXUSR ? "x" : "-")
#define IS_RGRP(mode) ((mode) & S_IRGRP ? "r" : "-")
#define IS_WGRP(mode) ((mode) & S_IWGRP ? "w" : "-")
#define IS_XGRP(mode) ((mode) & S_IXGRP ? "x" : "-")
#define IS_ROTH(mode) ((mode) & S_IROTH ? "r" : "-")
#define IS_WOTH(mode) ((mode) & S_IWOTH ? "w" : "-")
#define IS_XOTH(mode) ((mode) & S_IXOTH ? "x" : "-")

void uls_without_flags();
void uls_directory_search(int argc, char **argv);

typedef struct s_file {
    char *name;
    int index;
    bool is_directory;

    char* num_links;
    char* user_name;
    char* group_name;
    char* size;
    char* lm_day;
    char* lm_time;
    char* lm_month;
    char* perms;
    char* linked_file;
    char* acl_str;

    struct stat info;

    struct s_file *next;
}              t_file;

void free_files(t_file *head);
void add_file(t_file **head, char *name, int index);
void add_file_l(t_file **head, char *name, int index);
void sort_files(t_file **head);
t_file* get_index_file(t_file* list, int index);
int get_col_width(int max_lenght);
int get_rows(int col, int count);
int get_cols(int w_cols, int width);
void print_directories(t_file *head, int is_terminal, int file_count, int directory_count);
void print_files(t_file *head, int is_terminal);
void mx_print_tab(int width, int len);

void printl();

char *get_permissions(struct stat *info);
void get_lm_date(t_file **file, struct stat *info);

void printFileInfo(struct stat *info, t_file *filename);

void full_list(t_file **head);
int get_file_count(t_file *head);
int get_lenght(t_file *head);
int get_num_tabs(int width, int len);

t_flag* get_flags(int argc, char **argv);
bool is_flag(char flag);
void add_flag(t_flag** flags, char flag);
