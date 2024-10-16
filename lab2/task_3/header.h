#ifndef FUND__HEADER_H
#define FUND__HEADER_H

#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include "string.h"
#include "float.h"
#include <stdarg.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR, OVERFLOW_ERROR
};

void compute_prefix_function(char* pattern, int* pi, int m);
enum status find_pattern(char* pattern, char* file_path);
enum status file_pocessing(char *pattern, int num_files, ...);
#endif //FUND__HEADER_H
