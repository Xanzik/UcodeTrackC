#include "../inc/uls.h"

void add_file(t_file **head, char *name, int index, t_flag *flags, char *path) {
    t_file *new_node = malloc(sizeof(t_file));
    new_node->name = mx_strdup(name);
    new_node->next = NULL;
    new_node->index = index;
    if(flags->l) {
        new_node->path = name;
        if(path != NULL)
            new_node->path = mx_strdup(path);
        new_node->num_links = NULL;
        new_node->user_name = NULL;
        new_node->group_name = NULL;
        new_node->size = NULL;
        new_node->lm_day = NULL;
        new_node->lm_time = NULL;
        new_node->lm_month = NULL;
        new_node->perms = NULL;
        new_node->linked_file = NULL;
        new_node->acl_str = NULL;
        if(lstat(new_node->path, &(new_node->info)) == 0) {
            struct passwd *pw = getpwuid(new_node->info.st_uid);
            struct group *gr = getgrgid(new_node->info.st_gid);
            new_node->perms = get_permissions(&new_node->info);
            new_node->num_links = mx_itoa(new_node->info.st_nlink);
            new_node->user_name = pw ? mx_strdup(pw->pw_name) : mx_itoa(new_node->info.st_uid);
            new_node->group_name = gr ? mx_strdup(gr->gr_name) : mx_itoa(new_node->info.st_gid);
            new_node->size = mx_itoa(new_node->info.st_size);
            get_lm_date(&new_node, &new_node->info);
            char *link = get_linked_file(new_node);
            if(link) {
                new_node->linked_file = mx_strdup(link);
            }
            else {
                new_node->linked_file = NULL;
            }
            mx_strdel(&link);
        }
        
    }
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
                t_file *temp = sorted;
                while (temp->next != NULL && mx_strcmp(current->name, temp->next->name) > 0) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
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

void full_list(t_file **head, t_flag *flags) {
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
        add_file(head, path, index, flags, NULL);
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

char *get_path_dir(char *dir, char* file) {
    char *path = mx_strnew(mx_strlen(dir) + mx_strlen(file) + 1);
    mx_strcpy(path, dir);
    mx_strcat(path, "/");
    mx_strcat(path, file);
    return path;
}
