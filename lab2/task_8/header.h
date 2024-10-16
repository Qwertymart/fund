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
#define EPS 1e-6

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

int valid(int base, char * number);
void reverse(char ** number, int len);
void sum_of_two_numbers(char ** result, char * number, int base, int *len_res, int len_numbers);


#endif //FUND__HEADER_H
