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
    bool is_directory;
    struct s_file *next;
}              t_file;

void free_files(t_file *head);
void add_file(t_file **head, char *name);
t_file *new_file(char *name);
void sort_files(t_file **head);
void print_directories(t_file *head, int is_terminal, int file_count, int directory_count);
void print_files(t_file *head, int is_terminal, char **argv, int file_count);

void print_info(const char* filename);
void printl();

void printPermissions(mode_t mode);
void printFileInfo(struct stat *info, char *filename);
