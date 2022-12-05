int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_strcpy(char *dst, const char *src);

char *mx_strdup(const char *str) {
    int lenght = mx_strlen(str);
    char *cpy = mx_strnew(lenght);
    return mx_strcpy(cpy, str);
}
