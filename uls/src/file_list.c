#include "../inc/uls.h"

void add_file(t_file **head, char *name, int index) {
    t_file *new_node = (t_file *) malloc(sizeof(t_file));
    new_node->name = mx_strdup(name);
    new_node->next = NULL;
    new_node->index = index;
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
        if (sorted == NULL || mx_strcmp(current->name, sorted->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            if (current->is_directory) { // если текущий файл - директория
                sort_files(&current); // вызываем sort_files для этой директории
            }
            else {
                t_file *temp = sorted;
                while (temp->next != NULL && mx_strcmp(current->name, temp->next->name) > 0) {
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

int get_file_count(t_file *head) {
    int count = 0;
    t_file *current = head;
    while(current->next != NULL && current->name != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void full_list(t_file **head) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    int index = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, ".") == 0 
            || mx_strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.') {
                continue;
        }
        char *path = entry->d_name;
        add_file(head, path, index);
        index++;
    }
    closedir(dir);
}

t_file* get_index_file(t_file* list, int index) {
    int i = 0;
    while(list) {
        if(i == index)
            return list;
        list = list->next;
        ++i;
    }
    return NULL;
}

void print_directories(t_file *head, int is_terminal, int file_count, int directory_count) {
    DIR *dir;
    struct dirent *de;
    t_file *current = head;
    if(file_count > 1)
        sort_files(&current);
    int step = 0;
    while (current != NULL) {
        if(directory_count != 1 || file_count > 0) {
            mx_printstr(current->name);
            mx_printstr(":\n");
        }
        dir = opendir(current->name);

        // Create a list of files for this directory
        t_file *dir_files = NULL;
        int index = 0;
        while ((de = readdir(dir)) != NULL) {
            if(mx_strcmp(de->d_name, ".") == 0 
                || mx_strcmp(de->d_name, "..") == 0
                || de->d_name[0] == '.'){
                continue;
            }
            char *path = de->d_name;
            add_file(&dir_files, path, index);
            index++;
        }

        // Sort the files in this directory
        sort_files(&dir_files);

        // Print the files in this directory
        print_files(dir_files, is_terminal);

        // Free the list of files for this directory
        free_files(dir_files);

        step++;
        if (!is_terminal) {
            if(step != directory_count)
                mx_printstr("\n");
        }
        else {
            if(step != directory_count)
                mx_printstr("\n");
        }
        closedir(dir);
        current = current->next;
    }
}

