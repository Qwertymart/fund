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

enum status str_to_int(const char *str, int * result);
enum status str_to_double(char* str, double* result);
enum status fast_pow(double x, int n, double *result);
double geometric_mean(double* result, int count, ...);

#endif //FUND__HEADER_H
