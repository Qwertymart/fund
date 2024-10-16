#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "ctype.h"
#include "string.h"
typedef long int li;

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

int is_valid_double(const char* str) {
    if (strlen(str) > 24){
        return 0;
    }
    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '.' && *p != '-' && *p != '+' && *p != 'e') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_double(char* str, double* result){

    if (!(is_valid_double(str))){
        return INPUT_ERROR;
    }
    char *endptr;
    *result = strtod(str, &endptr);
    if ((*result == HUGE_VAL || *result == -HUGE_VAL))
    {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

double f1(double x) {
    if (x == 0) {
        return 1;
    }
    return log(1 + x) / x;
}

double f2(double x) {
    return exp(-x * x / 2);
}

double f3(double x) {
    if (x == 1) {
        return log(1 / (1 - x));
    }
    return log(1 / (1 - x));
}

double f4(double x) {
    return pow(x, x);
}


void trapezoidal(double (*f)(double), double a, double b, double eps, double* new_result) {
    double h = (b - a);
    double sum = (f(a) + f(b)) / 2;
    double old_result;
    *new_result = sum * h;
    int n = 1;

    do {
        old_result = *new_result;
        n *= 2;
        h /= 2;
        sum = 0;
        for (int i = 1; i < n; i += 2) {
            sum += f(a + i * h);
        }
        *new_result = old_result / 2 + sum * h;
    } while (fabs(*new_result - old_result) > eps);


}

int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    double eps;

    enum status f = str_to_double(argv[1], &eps);
    if (f == INPUT_ERROR || eps <= 0){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    double a, b, c, d;
    trapezoidal(f1, 0, 1, eps, &a);
    trapezoidal(f2, 0, 1, eps, &b);
    trapezoidal(f3, 0, 1 - eps, eps, &c);
    trapezoidal(f4, 0, 1, eps, &d);

    printf("a) %.10f\n", a);
    printf("b) %.10f\n", b);
    printf("c) %.10f\n", c);
    printf("d) %.10f\n", d);

    return 0;
}
