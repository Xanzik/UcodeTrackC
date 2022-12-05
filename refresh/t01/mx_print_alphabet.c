void mx_printchar(char c);

void mx_print_alphabet(void) {
	for (int x = 65; x < 91; x+=2) {
	        mx_printchar(x);
	        mx_printchar(x + 33);
    }
    mx_printchar('\n');
}

