#include "../inc/pathfinder.h"

void print_path(int max, t_matrix **array, int start, int end, t_circe *name) {
    int root = 1;
    int value = INT_MAX;
    max--;
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j <= max; j++) {
            array[i][j].path = false;
        }
    }
    for (int i = 0; i <= max; i++)
        if ((value > array[i][end].sum) && (array[i][end].sum > 0))
            value = array[i][end].sum;
    for (int i = 0; i <= max; i++) {
        if (value == array[i][end].sum) {
            array[i][end].path = true;
            int value = array[i][end].sum - array[i][end].val;
            build_path(array, i, value, max);
        }
    }
    root = 1;
    for (int rep = 0; rep < root; rep++) {
        int sum[end];
        int roots = 0;
        mx_printstr("========================================\n");
        mx_printstr("Path: ");
        mx_printstr(name[start].name);
        mx_printstr(" -> ");
        mx_printstr(name[end].name);
        mx_printstr("\nRoute: ");
        mx_printstr(name[start].name);
        for (int i = start; i != end;) {
            int repeat = 0;
            for (int j = 0; j <= max; j++) {
                if (array[i][j].path == true) {
                    repeat++;
                }
            }
            if (repeat == 1) {
                for (int j = 0; j <= max; j++) {
                    if (array[i][j].path == true) {
                        mx_printstr(" -> ");
                        mx_printstr(name[j].name);
                        sum[roots] = array[i][j].val;
                        roots++;
                        i = j;
                    break;
                    }
                }
            }
            else if (repeat > 1) {
                for (int j = 0; j <= max; j++) {
                    repeat = 0;
                    if (array[i][j].path == true) {

                        for (int k = j; k <= max; k++) {
                            if (array[j][k].path == true)
                                repeat++;
                        }

                        if (repeat <= 1) {
                            array[i][j].path = false;
                            root++;
                        }
                        mx_printstr(" -> ");
                        mx_printstr(name[j].name);
                        sum[roots] = array[i][j].val;
                        roots++;
                        i = j;
                        break;
                    }
                }
            }
        }

        mx_printstr("\nDistance: ");
        if (roots == 1) {
            mx_printint(sum[0]);
        }
        else {
            int s = sum[0];
            mx_printint(sum[0]);
            for (int i = 1; i < roots; i++) {
                mx_printstr(" + ");
                mx_printint(sum[i]);
                s += sum[i];
            }
            mx_printstr(" = ");
            mx_printint(s);
        }
        mx_printstr("\n");
        mx_printstr("========================================\n");
    }
}
