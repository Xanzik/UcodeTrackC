int mx_strcmp(const char *s1, const char *s2);

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int left = 0;
	int right = size - 1;
	int mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		(*count)++;
		if (mx_strcmp(s, arr[mid]) == 0)
			return mid;
		if (mx_strcmp(s, arr[mid]) > 0) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	*count = 0;
	return -1;
}

