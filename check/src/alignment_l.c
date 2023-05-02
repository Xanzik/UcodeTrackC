#include "../inc/uls.h"

void info_lenght(t_file **files) {
    t_lenghts *lenghts = fill_lenghts(files);
    get_space(files, lenghts);
    free(lenghts);
}

t_lenghts *fill_lenghts(t_file** files) {
    t_lenghts *lenghts = malloc(sizeof(t_lenghts));
    lenghts->lenght_num_links = get_max_num_links(files);
    lenghts->lenght_size = get_max_size(files);
    lenghts->lenght_gr_name = get_max_gr_name(files);
    lenghts->lenght_user_name = get_max_user_name(files);
    lenghts->lenght_day = get_max_day(files);
    lenghts->lenght_time = get_max_time(files);
    return lenghts;
}

int get_max_num_links(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->num_links);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

int get_max_size(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->size);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

int get_max_gr_name(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->group_name);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

int get_max_user_name(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->user_name);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

int get_max_day(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->lm_day);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

int get_max_time(t_file** files) {
    t_file *file = *files;
    int max_lenght = 0;
    while(file) {
        int len = mx_strlen(file->lm_time);
        if(len > max_lenght) {
            max_lenght = len;
        }
        file = file->next;
    }
    return max_lenght;
}

void get_space(t_file **files, t_lenghts *lenghts) {
    t_file *file = *files;
    while(file) {
    file->num_links = set_front_space(file->num_links, lenghts->lenght_num_links);
    file->size = set_front_space(file->size, lenghts->lenght_size);
    file->lm_day = set_front_space(file->lm_day, lenghts->lenght_day);
    file->lm_time = set_front_space(file->lm_time, lenghts->lenght_time);
    file->user_name = set_back_space(file->user_name, lenghts->lenght_user_name);
    file->group_name = set_back_space(file->group_name, lenghts->lenght_gr_name);
    file = file->next;
    }
}

char *set_front_space(char *str, int max_lenght) {
    int lenght = mx_strlen(str);
    if(lenght == max_lenght) {
        return str;
    }
    char *new = (char*) malloc((max_lenght + 1) * sizeof(char));
    int space = max_lenght - lenght;
    for(int i = 0; i < space; i++) {
        new[i] = ' ';
    }
    mx_strcpy(&new[space], str);
    return new;
}

char *set_back_space(char *str, int max_lenght) {
    int lenght = mx_strlen(str);
    if(lenght == max_lenght) {
        return str;
    }
    char *new = (char*) malloc((max_lenght + 1) * sizeof(char));
    mx_strcpy(new, str);
    for(int i = lenght; i < max_lenght; i++) {
        new[i] = ' ';
    }
    return new;
}
