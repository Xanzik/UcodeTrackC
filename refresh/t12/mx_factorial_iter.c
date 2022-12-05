int mx_factorial_iter(int n) {
    if (n > 0) {
    	int factorial;
    	for (factorial = 1; n > 1; factorial *= (n--)) {
			if ((factorial * n) > 2147483647 || (factorial * n) < 0) {
				return 0;
			}
        }
   		return factorial;
    }
    else if (n == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
