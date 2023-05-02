#pragma once

#include "../libmx/inc/libmx.h"

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define FLAGS "lRC1AaGeT@rtucS"

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

typedef struct s_flag {
    int l;
    int R;
    int a;
    int A;
    int C;
    int G;
    int one;
    int e;
    int count;
    int T;
    int at;
    int r;
    int u;
    int c;
    int S;
    int t;
    int error;
}               t_flag;

typedef struct s_file {
    char *name;
    int index;
    char *path;

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

typedef struct s_lenghts {
    int lenght_num_links;
    int lenght_size;
    int lenght_gr_name;
    int lenght_user_name;
    int lenght_day;
    int lenght_time;
}               t_lenghts;

void uls_without_flags(t_flag *flags);
void uls_directory_search(int argc, char **argv, t_flag *flags);

void add_file(t_file **head, char *name, int index, t_flag *flags, char *path);
void full_list(t_file **head,  t_flag *flags, DIR *dir);
void free_files(t_file *head);
char *get_path_dir(char *dir, char* file);
t_file* get_index_file(t_file* list, int index);
int get_file_count(t_file *head);
int get_lenght(t_file *head);
int get_num_tabs(int width, int len);

void print_directories(t_file *head, int is_terminal, int file_count, int directory_count, t_flag *flags);
void print_files(t_file *head, int is_terminal, t_flag *flags);
void printl(t_flag *flags, int argc, char **argv);

int get_col_width(int max_lenght);
int get_rows(int col, int count);
int get_cols(int w_cols, int width);
void mx_print_tab(int width, int len);

char *get_permissions(struct stat *info);
void get_lm_date(t_file **file, struct stat *info, t_flag *flags);

void printFileInfo(t_file *filename, t_flag *flags);

t_flag* get_flags(int argc, char **argv);
void add_flag(t_flag** flags, char flag);
bool is_flag(char flag);

void info_lenght(t_file **files);
t_lenghts *fill_lenghts(t_file** files);
int get_max_num_links(t_file** files);
int get_max_size(t_file** files);
int get_max_gr_name(t_file** files);
int get_max_user_name(t_file** files);
int get_max_day(t_file** files);
int get_max_time(t_file** files);
int total_block(t_file **files);
char* get_linked_file(t_file *file);
char get_extra_perms(t_file *file);
void get_space(t_file **files, t_lenghts *lenghts);
char *set_front_space(char *str, int max_lenght);
char *set_back_space(char *str, int max_lenght);

void print_current_l(t_flag *flags, DIR *dir, char *half);
void print_all_l(char **argv, t_flag *flags, int argc);
void print_dir_l(t_file *head, int file_count, int directory_count, t_flag *flags);

void print_dir_err(char *error, char *path);

void sort_err(char **list, int n);
void sort_by_mtime(t_file **head);
void sort_files(t_file **head, t_flag *flags);
void sort_r(t_file **head);
void sort_by_atime(t_file **head);
void sort_by_ctime(t_file **head);
void sort_by_size(t_file **head);

void print_R(t_flag *flags, DIR *dir, char *path, bool first, bool end, int num);
void full_list_dir(t_file **head, t_flag *flags, DIR *dir, char *half);
void output_R_dir(int argc, char **argv, t_flag *flags);
bool check_dir(char **argv, int argc);
char *get_acl_text(t_file *file, t_flag *flags);
void acL_params(char **params, int i);
void output_xattr(const char *path);
void output_acl(const char* acl);
