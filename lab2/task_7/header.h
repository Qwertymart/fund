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

enum root{
    SUCCESS,
    INPUT_ERROR,
    YES,
    NO,
};

enum root dichotomy(double* result, double (*func)(double), double a, double b, double epsilon);
double func1(double x);
double func2(double x);
double func3(double x);
double func4(double x);


#endif //FUND__HEADER_H
