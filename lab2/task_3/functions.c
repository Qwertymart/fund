#include "header.h"


void compute_prefix_function(char* pattern, int* pi, int m)
{
    int len = 0;
    pi[0] = 0;

    for (int i = 1; i < m; ++i) {
        while (len > 0 && pattern[i] != pattern[len]) {
            len = pi[len - 1];
        }
        if (pattern[i] == pattern[len]) {
            ++len;
        }
        pi[i] = len;
    }
}

enum status find_pattern(char* pattern, char* file_path)
{
    FILE* f = fopen(file_path, "r");
    if (f == NULL) {
        return ERROR_OPEN;
    }

    int m = strlen(pattern);

    int* pi = (int*)malloc(m * sizeof(int));
    if (pi == NULL) {
        fclose(f);
        return MEMORY_ERROR;
    }

    compute_prefix_function(pattern, pi, m);

    int j = 0;
    int line_number = 1;
    int position_in_line = 1;
    int start_pos = 1;
    char c;
    while ((c = fgetc(f)) != EOF) {
        while (j > 0 && pattern[j] != c) {
            j = pi[j - 1];
        }
        if (pattern[j] == c) {
            j++;
        }

        if (j == m) {
            start_pos = position_in_line - m + 1;
            printf("Найдено вхождение в строке %d на позиции %d - файл %s\n", line_number, start_pos, file_path);
            j = pi[j - 1];
        }

        if (c == '\n') {
            line_number++;
            position_in_line = 1;
        } else {
            position_in_line++;
        }
    }


    free(pi);
    fclose(f);

    return SUCCESS;
}



enum status file_pocessing(char *pattern, int num_files, ...)
{
    va_list(files);
    va_start(files, num_files);

    for (int i = 0; i < num_files; ++i){
        char* file_path = va_arg(files, char *);
        enum status f = find_pattern(pattern, file_path);
        if (f != SUCCESS) {
            va_end(files);
            return f;
        }
    }
    va_end(files);
    return SUCCESS;
}