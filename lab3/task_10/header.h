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
#include <time.h>

void print_tree(FILE * input, FILE * output);

#endif //FUND__HEADER_H
