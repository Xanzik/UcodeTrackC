#include "../inc/pathfinder.h"

void pathfinder(int size, t_matrix **array, int start, int end, t_circe *name) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            array[i][j].sum = INT_MAX;
            array[i][j].was = false;
            if (array[i][j].val == INT_MAX)
                array[i][j].was = true;
        }
    }
    for (int i = 0; i < size; i++) { 
        if (array[start][i].was == false) {
            array[start][i].sum = array[start][i].val;
            fill_in_the_array(array, i, array[start][i].sum, size);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            array[i][j].was = false;
            if (array[i][j].val == INT_MAX)
                array[i][j].was = true;
        }
    }
    print_path(size, array, start, end, name);
}
