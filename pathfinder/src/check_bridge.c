#include "../inc/pathfinder.h"

void check_invalid(t_circe *list, char *text, int lenght_of_bridge) {
    int check = 0;
    while (*text != '\0') {
        if (*text != '\0') {
            if (mx_strlen(*mx_strsplit(text, '-')) < mx_strlen(*mx_strsplit(text, ','))) {
                check = 0;
                for (int i = 0; i < lenght_of_bridge; i++) {
                    if (mx_strcmp(list[i].name, *mx_strsplit(text, '-')) == 0)
                        check++;
                }
                if (check == 0) {
                    write(2, "error: invalid number of islands\n", 33);
                    exit(-1);
                }
                while (*text != '-' && *text != '\0')
                    text++;
            } else {
                check = 0;
                for (int i = 0; i < lenght_of_bridge; i++) {
                    if (mx_strcmp(list[i].name, *mx_strsplit(text, ',')) == 0)
                        check++;
                }
                if (check == 0) {
                    write(2, "error: invalid number of islands\n", 33);
                    exit(-1);
                }
                while (!mx_isspace(*text) && *text != '\0')
                    text++;
            }
            text++;
        }
    }
}
