#include "../inc/pathfinder.h"

void setup(t_matrix **array, t_circe *list, int lenght_of_bridge, char *str) {
    for (int i = 0; i < lenght_of_bridge; i++) {
        for (int j = 0; j < lenght_of_bridge; j++) {
            array[i][j].val = INT_MAX;
            array[i][j].sum = INT_MAX;
            array[i][j].was = false;
            array[i][j].path = false;
        }
    }
    int check = 0;
    while (*str != '\0') {
        int x = 0;
        int y = 0;

        for (int i = 0; i < lenght_of_bridge; i++) {
            char *s = mx_strcut(str, '-');
            if (mx_strcmp(list[i].name, s) == 0) {
                x = list[i].n;
                while (*str != '-' && *str != '\0') {
                    str++;
                }
                str++;
            }
            mx_strdel(&s);
        }

        for (int i = 0; i < lenght_of_bridge; i++) {
            char *c = mx_strcut(str, ',');
            if (mx_strcmp(list[i].name, c) == 0) {
                y = list[i].n;
                while (*str != ',' && *str != '\0') {
                    str++;
                }
                str++;
            }
            mx_strdel(&c);
        }

        array[x][y].val = mx_atoi(str);
        array[y][x].val = mx_atoi(str);
        check += mx_atoi(str);
        while (!mx_isspace(*str) && *str != '\0')
            str++;
        if (*str != '\0')
            str++;
    }
    if (check > INT_MAX || check < 0) {
        write(2, "error: sum of bridges lengths is too big\n", 41);
    }
    for (int i = 0; i < lenght_of_bridge; i++)
        array[i][i].val = INT_MAX;

}
