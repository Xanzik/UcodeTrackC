#include "../inc/pathfinder.h"

void mx_error_check(int argc, char **argv) {
    if (argc != 2) {
        write(2, "usage: ./pathfinder [filename]\n", 31);
        exit(-1);
    }
    int check = open(argv[1], O_RDONLY);   
    if (check == -1) {
        write(2, "error: file ", 12);
        write(2, argv[1], mx_strlen(argv[1]));
        write(2, " does not exist\n", 16);
        exit(-1);
    }
    close(check);
    char *str = mx_file_to_str(argv[1]);
    char *chap = mx_file_to_str(argv[1]);
    if (mx_strlen(str) <= 0) {
        write(2, "error: ", 8);
        write(2, argv[1], mx_strlen(argv[1]));
        write(2, " is empty\n", 10);
        exit(-1);
	}
    while (*str != '\n') {
        if (!mx_isdigit(*str)) {
            write(2, "error: line 1 is not valid\n", 27);
            exit(-1);
        }
        str++;
    }
    str++;
    int count = 0;
    while(*chap != '\0') {
        if(*chap == '\n') {
            count++;
        }
        chap++;
    }


    int line = 1;
    while (*str != '\0') {
        line++;
        if(count == line) {
            break;
        }
        while (*str != '-')
            str++;
        
        str++;
        if(!mx_isdigit(*str)
            && !mx_isalpha(*str)) {
            write(2, "error: line ", 13);
            mx_printint(line);
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        while (*str != ',')
            str++;
        str++;
        if(!mx_isdigit(*str)) {
            write(2, "error: line ", 13);
            mx_printint(line);
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        while (!mx_isspace(*str))
            str++;
            
        if(!mx_isspace(*str)) {
            write(2, "error: line ", 13);
            mx_printint(line);
            write(2, " is not valid\n", 14);
            exit(-1);
        }
        if (*str != '\0')
            str++;
    }
}
