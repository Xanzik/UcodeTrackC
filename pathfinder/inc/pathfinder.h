#pragma once

#include "../libmx/inc/libmx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>

#define INT_MAX 2147483647

typedef struct s_circe {
    char *name;
    int n;
}   			t_circe;

typedef struct s_matrix {
	int val;
	int sum;
	bool was;
	bool path;
}				t_matrix;


char *mx_delete_duplicates(char *str, t_circe *list, int lenght_of_bridge, int i);

void init_points(t_circe *list, char *str, int lenght_of_bridge);

void fill_in_the_array(t_matrix **array, int from, int sum, int size);

void pathfinder(int size, t_matrix **array, int start, int end, t_circe *name);

void build_path(t_matrix **array, int from, int value, int size);

void print_path(int max, t_matrix **array, int start, int end, t_circe *name);

void setup(t_matrix **array, t_circe *list, int leght_of_bridge, char *str);

void mx_error_check(int argc, char **argv);

void check_invalid(t_circe *list, char *text, int lenght_of_bridge);
