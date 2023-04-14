#include "../inc/uls.h"

t_file *new_file(char *name) {
    t_file *file = (t_file *)malloc(sizeof(t_file));
    file->name = name;
    file->next = NULL;
    return file;
}

void add_file(t_file **head, char *name) {
    t_file *new_node = (t_file *) malloc(sizeof(t_file));
    new_node->name = mx_strdup(name);
    new_node->next = NULL;
    t_file *last = *head;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void free_files(t_file *head) {
    t_file *current = head;
    while (current != NULL) {
        t_file *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}

void sort_files(t_file **head) {
    t_file *sorted = NULL;
    t_file *current = *head;
    while (current != NULL) {
        t_file *next = current->next;
        if (sorted == NULL || mx_cmp_str(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            if (current->is_directory) { // если текущий файл - директория
                sort_files(&current); // вызываем sort_files для этой директории
            }
            else {
                t_file *temp = sorted;
                while (temp->next != NULL && mx_cmp_str(current->name, temp->next->name) > 0) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }
        current = next;
    }
    *head = sorted;
}

void print_files(t_file *head, int is_terminal, char **argv, int file_count) {
    t_file *current = head;
    if(file_count != 1)
        sort_files(&current);
    int step = 1;
    while (current != NULL) {
        if (access(argv[step], F_OK) != -1) {
            mx_printstr(current->name);
            if (is_terminal) {
                if(step != file_count && current->next != NULL) {
                    mx_printstr("   ");
                }
                if(step == file_count) {
                    mx_printstr("\n");
                }
            } else {
                if(step != file_count) {
                    mx_printstr("\n");
                }
                if(step == file_count) {
                    mx_printstr("\n");
                }
            }
        }
        step++;
        current = current->next;
    }
}

void print_directories(t_file *head, int is_terminal, int file_count, int directory_count) {
    DIR *dir;
    struct dirent *de;
    t_file *current = head;
    sort_files(&current);
    int step = 0;
    while (current != NULL) {
        bool check = 0;
        if(directory_count != 1 || file_count > 0) {
            mx_printstr(current->name);
            mx_printstr(":\n");
        }
        dir = opendir(current->name);

        // Create a list of files for this directory
        t_file *dir_files = NULL;
        while ((de = readdir(dir)) != NULL) {
            if(mx_strcmp(de->d_name, ".") == 0 || mx_strcmp(de->d_name, "..") == 0){
                continue;
            }
            add_file(&dir_files, de->d_name);
        }

        // Sort the files in this directory
        sort_files(&dir_files);

        // Print the files in this directory
        t_file *dir_current = dir_files;
        while (dir_current != NULL) {
            if (is_terminal) {
                mx_printstr(dir_current->name);
                mx_printstr("   ");
            } else {
                mx_printstr(dir_current->name);
                mx_printstr("\n");
            }
            check = 1;
            dir_current = dir_current->next;
        }

        // Free the list of files for this directory
        free_files(dir_files);

        step++;
        if (!is_terminal) {
            if(step != directory_count)
                mx_printstr("\n");
        }
        else {
            mx_printstr("\n");
            if(check && step != directory_count)
                mx_printstr("\n");
        }
        closedir(dir);
        current = current->next;
    }
}

