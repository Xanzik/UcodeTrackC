#include "../inc/pathfinder.h"

char *mx_delete_duplicates(char *str, t_circe *list, int lenght_of_bridge, int i) {
    for (int x = 0; x < lenght_of_bridge; x++) {
        char *c = mx_strcut(str, ',');
        char *s = mx_strcut(str, '-');
        if (mx_strlen(s) < mx_strlen(c)) {
            for (int j = 0; j < i; j++) {
                if (mx_strcmp(s, list[j].name) == 0) {
                    while (*str != '-' && *str != '\0')
                        str++;
                    str++;
                    x--;
                    break;
                }
            }
        } else {
            for (int j = 0; j < i; j++) {
                if (mx_strcmp(c, list[j].name) == 0) {
                    while (!mx_isspace(*str) && *str != '\0')
                        str++;
                    str++;
                    x--;
                    break;
                }
            }
        }
        mx_strdel(&c);
        mx_strdel(&s);
    }
    return str;
}
