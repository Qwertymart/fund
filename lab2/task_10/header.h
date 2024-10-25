
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

enum status{
     SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR, OVERFLOW_ERROR
};

enum status polynomial(double a, double **coef, int degree, ...);

#endif //FUND__HEADER_H
