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
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR, OVERFLOW_ERROR
};

int oversscanf(char *str, const char* format, ...);
int overfscanf(FILE* f, char* format, ...);


int Ro(char* str, int* index_plus, char format_end);
int Zr(char* str, char format_end, int* index_plus);
enum status Cv(char* str, char format_end, int base, int *result, int* index_plus);

#endif //FUND__HEADER_H
