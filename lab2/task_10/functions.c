#include "header.h"

double evaluate_polynomial(double a, double *coefs, int degree) {
    double result = 0;
    double power_of_a = 1;

    for (int i = 0; i <= degree; ++i) {
        result += coefs[i] * power_of_a;
        power_of_a *= a;
    }
    return result;
}

enum status polynomial(double a, double **coef, int degree, ...)
{
    if (degree < 0)
    {
        return INPUT_ERROR;
    }
    (*coef) = (double *)malloc((degree + 1) * sizeof(double));
    if (*coef == NULL)
    {
        return MEMORY_ERROR;
    }
    int n = degree;
    double *f_coef = (double *)malloc((degree + 1) * sizeof(double));
    if (f_coef == NULL)
    {
        free(*coef);
        return MEMORY_ERROR;
    }

    va_list args;
    va_start(args, degree);

    for (int i = 0; i <= degree; ++i)
    {
        f_coef[i] = va_arg(args, double );
    }
    va_end(args);

    (*coef)[0] = evaluate_polynomial(a, f_coef, degree);

    for (int i = 1; i <= degree; ++i) {
        for (int j = 0; j <= degree - i; ++j) {
            f_coef[j] = f_coef[j + 1] * (j + 1);
        }
        (*coef)[i] = evaluate_polynomial(a, f_coef, degree - i) / i;
    }


    free(f_coef);
    return SUCCESS;

}