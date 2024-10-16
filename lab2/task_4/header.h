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

enum conv{
    CONVEX, NOT_CONVEX
};

typedef struct {
    double x;
    double y;
} Point;

enum status convex(enum conv* result, int count, ...);
enum status polynomial(double *result, double x, int n, ...);
int is_valid_int(const char* str);
enum status str_to_int(const char *str, int * result, int base);
void int_to_str_base(int num, int base, char* str);
enum status is_kaprekar(int num, int base, int *kaprekar);
enum status find_kaprekar(int base, int num_args, ...);

#endif //FUND__HEADER_H
