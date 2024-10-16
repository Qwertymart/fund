#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "ctype.h"
#include "limits.h"
#include "float.h"
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

void func_a(double x, double eps, double* a) {
    *a = 0;
    double temp = 1.0;
    double fact = 1.0;
    int n = 0;

    while (fabs(temp) >= eps) {
        *a += temp;
        ++n;
        if (n != 0) {
            fact *= n;
        }
        temp = pow(x, n) / fact;
    }
}

li factorial(int n) {
    li result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
        if (result * (i + 1) > LONG_MAX){
            return -1;
        }
    }
    return result;
}

void func_b(double x, double eps, double* b) {
    *b = 1.0;
    double temp = 1.0;
    int n = 0;

    while (fabs(temp) >= eps) {
        temp *= -x * x / ((2*n + 1) * (2*n + 2));
        *b += temp;
        ++n;
    }
}

int  func_c(double x, double eps, long double* c) {
    int n = 0;
    *c = 0;
    long double element = 1;

    while (fabs(element) >= eps) {
        *c += element;
        if (n == 100000){
            return -1;
        }
        ++n;
        element *= (9.0 * n * n * x * x) / (9.0 * n * n - 9.0 * n + 2.0);
        if (isinf(*c)) {
            return -1;
        }
    }
    return 0;
}

int func_d(double x, double eps, double* d) {
    int n = 1;
    *d = 0;
    double element = -x * x / 2.0;

    while (fabs(element) >= eps) {
        *d += element;
        n++;
        element *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
        if (n > 100000) {
            return -1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    double x, eps;

    if (str_to_double(argv[1], &x) != SUCCESS ||
        str_to_double(argv[2], &eps) != SUCCESS ||
        eps <= 0) {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    double a, b, d;
    long double c;

    func_a(x, eps, &a);
    func_b(x, eps, &b);
    printf("Результаты вычислений:\n");
    printf("Сумма ряда A: %.15f\n", a);
    printf("Сумма ряда B: %.15f\n", b);

    if(!func_c(x, eps, &c)){
        printf("Сумма ряда C: %.15Lf\n", c);
    } else{
        printf("Ряд C не сходится при данном значении x\n");
    }
    if (!func_d(x, eps, &d)){
        printf("Сумма ряда D: %.15f\n", d);
    }else{
        printf("Ряд D не сходится при данном значении x\n");
    }

    return 0;
}