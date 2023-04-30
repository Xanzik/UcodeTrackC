#include "../inc/uls.h"

void print_dir_err(char *error, char *path) {
    mx_printerr("uls: ");
    mx_printerr(path);
    mx_printerr(": ");
    mx_printerr(error);
    mx_printerr("\n");
}

void sort_err(char **list, int n) {
    int i, j;
    char *temp;

    // Сортировка массива строк в алфавитном порядке с помощью сортировки пузырьком
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (mx_strcmp(list[j], list[j + 1]) > 0) {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}
