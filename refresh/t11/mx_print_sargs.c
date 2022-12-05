int mx_strcmp(const char *s1, const char *s2);
void mx_printchar(char c);
void mx_printstr(const char *s);
int mx_strlen(const char *s);

int main(int argc, char **argv) {
	char *temp = 0;
	for(int j = 1; j < argc; j++) {
		for(int i = 1; i < argc-j; i++) {
			if (mx_strcmp(argv[i], argv[i + 1]) > 0) {
				temp = argv[i];
				argv[i] = argv[i+1];
				argv[i+1] = temp; 
			}
		}
	}
	for (int i = 1; i < argc; i++) {
		mx_printstr(argv[i]);
		mx_printchar('\n');
	}
	return 0;
}

