#include "libmx.h"

bool mx_isdigit(int c) {
	if (c >= 48 && c <= 57)
		return 1;
	return 0;
}

int mx_atoi(const char *str) {
	bool is_negative = false;
	int current_index = 0;
	int result_number = 0;
	for (; str[current_index] != '\0'; current_index++)
		if (!mx_isspace(str[current_index])) break;
	if (str[current_index] == '-') {
		is_negative = true;
		current_index++;
	}
	for (; mx_isdigit(str[current_index]); current_index++) {
		result_number *= 10;
		result_number += str[current_index] - 48;
	}
	if (is_negative) result_number *= -1;
	return result_number;	
}
