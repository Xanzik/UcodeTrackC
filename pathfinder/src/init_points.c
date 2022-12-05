#include "../inc/pathfinder.h"

void init_points(t_circe *list, char *str, int lenght_of_bridge) {
    int i = 0;
    while (*str != '\n') {
        str++;
    }
    str++;
    while (*str != '\0') {
        char *tmp;
        if (i > 1) {
            str = mx_delete_duplicates(str, list, lenght_of_bridge, i);
        }
        if (mx_strlen(mx_strcut(str, '-')) < mx_strlen(mx_strcut(str, ','))) {
            list[i].name = mx_strcut(str, '-');
            list[i].n = i;
            tmp = mx_strcut(str, '-');
            i++;
            for (int j = 0; (mx_strlen(tmp) + 1) > j && *str != '\0'; j++) {
                str++;
            }
            free(tmp);
        }
        else {
            list[i].name = mx_strcut(str, ',');
            list[i].n = i;
            tmp = mx_strcut(str, ',');
            i++;
            for (int j = 0; (mx_strlen(tmp) + 1) > j && *str != '\0'; j++) {
                str++;
            }
            tmp = *mx_strsplit(str, '\n');
            for (int j = 0; (mx_strlen(tmp) + 1) > j && *str != '\0'; j++) {
                str++;
            }
            free(tmp);
        }
        if (i == lenght_of_bridge) {
            check_invalid(list, str, lenght_of_bridge);
            break;
        }
    }
}
