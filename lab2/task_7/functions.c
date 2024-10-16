#include "header.h"

enum root dichotomy(double* result, double (*func)(double), double a, double b, double epsilon)
{
    if (func(a) * func(b) >= 0)
    {
        return NO;
    }
    if (epsilon <= 0)
    {
        return INPUT_ERROR;
    }
    double mid;
    while ((b - a) / 2.0 > epsilon) {
        mid = (a + b) / 2.0;

        if (func(mid) == 0.0) {
            *result = mid;
            return YES;
        } else if (func(a) * func(mid) < 0) {
            b = mid;
        } else {
            a = mid;
        }
    }
    *result =  (a + b) / 2.0;
    return YES;
}



//x^2 - 2
double func1(double x)
{
    return x * x - 2;
}

// sin(x)
double func2(double x)
{
    return sin(x);
}

// x^3 - x - 2
double func3(double x)
{
    return x * x * x - x - 2;
}

// exp(x) - 5
double func4(double x)
{
    return exp(x) - 5;
}
