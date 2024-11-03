#ifndef FUND__HEADER_H
#define FUND__HEADER_H

enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR, OVERFLOW
};
#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include "string.h"
#include "float.h"
#include <stdarg.h>

typedef struct
{
    int id;
    char name[51];
    char surname[51];
    double salary;
}Employee;

int cmp_a(const void* a, const void* b);
int cmp_d(const void* a, const void* b);
enum status str_to_int(const char *str, int * result);
enum status str_to_double(char* str, double* result);


#endif //FUND__HEADER_H
