#include "../inc/uls.h"

void sort_files(t_file **head, t_flag *flags) {
    if(flags->S) {
        sort_by_size(head);
    } else if(flags->t && !flags->u && !flags->c) {
        sort_by_mtime(head);
    } else if(flags->u && flags->t && !flags->S) {
        sort_by_atime(head);
    } else if(flags->c && flags->t && !flags->S) {
        sort_by_ctime(head);
    } else if(!flags->t && !flags->S) {
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
    if(flags->r)
        sort_r(head);
}

void sort_r(t_file **head) {
    t_file *prev = NULL;
    t_file *current = *head;
    t_file *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void sort_by_mtime(t_file **head) {
    t_file *sorted = NULL;
    t_file *current = *head;
    while (current != NULL) {
        t_file *next = current->next;
        if (sorted == NULL || current->info.st_mtime > sorted->info.st_mtime) {
            current->next = sorted;
            sorted = current;
        } else {
            t_file *temp = sorted;
            while (temp->next != NULL && current->info.st_mtime <= temp->next->info.st_mtime) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}

void sort_by_atime(t_file **head) {
    t_file *sorted = NULL;
    t_file *current = *head;
    while (current != NULL) {
        t_file *next = current->next;
        if (sorted == NULL || current->info.st_atime > sorted->info.st_atime) {
            current->next = sorted;
            sorted = current;
        } else {
            t_file *temp = sorted;
            while (temp->next != NULL && current->info.st_atime <= temp->next->info.st_atime) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}

void sort_by_ctime(t_file **head) {
    t_file *sorted = NULL;
    t_file *current = *head;
    while (current != NULL) {
        t_file *next = current->next;
        if (sorted == NULL || current->info.st_ctime > sorted->info.st_ctime) {
            current->next = sorted;
            sorted = current;
        } else {
            t_file *temp = sorted;
            while (temp->next != NULL && current->info.st_ctime <= temp->next->info.st_ctime) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}

void sort_by_size(t_file **head) {
    t_file *sorted = NULL;
    t_file *current = *head;
    while (current != NULL) {
        t_file *next = current->next;
        if (sorted == NULL || current->info.st_size > sorted->info.st_size) {
            current->next = sorted;
            sorted = current;
        } else {
            t_file *temp = sorted;
            while (temp->next != NULL && current->info.st_size <= temp->next->info.st_size) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}
