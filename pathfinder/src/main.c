#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    mx_error_check(argc, argv);
    char *str = mx_file_to_str(argv[1]);
    int lenght_of_bridge = mx_atoi(str);
    t_matrix **array = (t_matrix **)malloc(lenght_of_bridge * sizeof(t_matrix *));
    for (int i = 0; i < lenght_of_bridge; i++) {
        array[i] = (t_matrix *)malloc(lenght_of_bridge * sizeof(t_matrix));
    }
    t_circe *list = (t_circe*) malloc (lenght_of_bridge * sizeof(t_circe));
    init_points(list, str, lenght_of_bridge);
    setup(array, list, lenght_of_bridge, str);
    for (int i = 0; i < lenght_of_bridge - 1; i++) {
        for (int j = i + 1; j < lenght_of_bridge; j++) {
            pathfinder(lenght_of_bridge, array, i, j, list);
        }
    }
    free(*array);
    free(list);
    mx_strdel(&str);
    return 0;
}
