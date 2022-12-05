void mx_sort_arr_int(int *arr, int size) {
    for (int i = 0; i < (size - 1); i++) {
        for (int j = (size - 1); j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                int tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

