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
    SUCCESS,
    INPUT_ERROR,
    HAS_FINITE_REPRESENTATION,
    DOESNT_FINITE_REPRESENTATION
};


void check_finite_representations(int base, int num_value, ...);

#endif //FUND__HEADER_H
