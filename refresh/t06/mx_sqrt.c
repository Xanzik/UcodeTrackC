int mx_sqrt(int x) {
	unsigned div = 1;
	unsigned result = 0;
	unsigned y = x;
	while (x > 0) {    
		x -= div;  
		div += 2; 
		result += x < 0 ? 0 : 1;
	}
	if ((result * result) == y)
		return result;
	return 0;
}
