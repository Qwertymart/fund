
#ifndef FUND__HEADER_H
#define FUND__HEADER_H


enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR
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


enum status convert_to_base(int num, int r, char** res, int* capacity);
int negative(int n);
int sum (int num1, int num2);
void print_num(int flag, char * res, int count);

#endif //FUND__HEADER_H
