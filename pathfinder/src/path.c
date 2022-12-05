#include "../inc/pathfinder.h"

void build_path(t_matrix **array, int from, int value, int size) {
    for (int i = 0; i <= size; i++) {
        if (value == array[i][from].sum) {
            array[i][from].path = true;
            int value = array[i][from].sum - array[i][from].val;
            build_path(array, i, value, size);
        }
    }
}
