#include "../inc/pathfinder.h"

void fill_in_the_array(t_matrix **array, int from, int sum, int size) {
    for (int i = 0; i < size; i++) { 
        if (array[from][i].was == false)
            if(array[from][i].val + sum < array[from][i].sum) {
                array[from][i].sum = array[from][i].val + sum;
                fill_in_the_array(array, i, array[from][i].sum, size);
        }
    }
}
