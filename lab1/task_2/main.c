#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "math.h"
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR
};

enum status str_to_double(char* str, double* result){
    char* end_ptr;
    *result = strtod(str, &end_ptr);
    if (errno == ERANGE && (*result == HUGE_VAL || *result == -HUGE_VAL))
    {
        return INPUT_ERROR;
    } else if (errno == ERANGE && *result == 0) {
        return INPUT_ERROR;
    } else if (*end_ptr != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

double limit_e(double eps){
    double current = 0.0;
    double previous = 0.0;
    int n = 1;

    do{
        previous = current;
        current = pow(1.0 + 1.0 / n, n);
        ++n;
    }while(fabs(current - previous)>eps);

    return  current;
}

double limit_pi(double eps) {
    double current = 4.0;
    double previous = 0.0;
    int n = 2;

    do {
        previous = current;
        current *= (4.0 * n * ( n - 1.0)) / pow(2.0 * n - 1.0, 2);
        ++n;
    } while (fabs(current - previous) > eps);

    return current ;
}

double limit_ln(double eps){
    double current = 0.0;
    double previous;
    int n = 1;

    do {
        previous = current;
        current = n*(pow(2.0, 1.0/n) - 1.0);
        ++n;
    } while (fabs(current - previous) > eps);

    return current;
}

double limit_2(double eps){
    double current = -0.5;
    double previous;
    int n = 1;

    do {
        previous = current;
        current = (2.0 * previous - pow(previous, 2.0) + 2.0)/2.0;
        ++n;
    } while (fabs(current - previous) > eps);

    return current;
}

double limit_g(double eps) {
    double current = 0.0;
    double previous;
    int n = 1;

    do {
        previous = current;
        current = 0.0;

        for (int k = 1; k <= n; ++k) {
            current += 1.0 / k;
        }

        current -= log(n);
        ++n;

    } while (fabs(current - previous) > eps);

    return current;
}

double rows_e(double eps){
    double current = 1.0;
    double previous;
    int n = 1;
    double fact = 1.0;

    do{
        previous = current;
        fact *= n;
        current += 1.0/fact;
        ++n;
    } while (fabs(current - previous) > eps);

    return current;
}

double rows_pi(double eps){
    double current = 0.0;
    double previous;
    int n = 1;
    double sign = 1.0;

    do{
        previous = current;
        current += 4 * (sign/(2*n - 1));
        sign = -sign;
        ++n;
    } while (fabs(current - previous) > eps);

    return current;
}

double rows_ln(double eps){
    double current = 0.0;
    double previous;
    int n = 1;
    double sign = 1.0;

    do{
        previous = current;
        current += sign/n;
        sign = -sign;
        ++n;
    } while (fabs(current - previous) > eps);

    return current;
}

double rows_2(double eps){
    double current = 1.0;
    double previous;
    int n = 2;
    double sign = 1.0;

    do{
        previous = current;
        current *= pow(2, pow(2, -n));
        sign = -sign;
        ++n;
    } while (fabs(current - previous) > eps);

    return current;

}

double rows_g(double epsilon)
{
    double previous = 0.0;
    double current = 0.5;
    int k = 2;
    double l = 0.0;
    do
    {
        previous = current;
        ++k;
        l = sqrt(k);
        if (fmod(l,1.0) == 0)
        {
            k++;
            l = (int)pow(k, 1.0/2.0);
        }
        current += 1.0/pow((int)l,2.0) - 1.0/k;

    } while (fabs(previous - current) >= epsilon);

    return (current - pow(M_PI,2) / 6);
}

double equation_e(double eps){
    double x = 1;
    double f = 1, df;
    while (fabs(f) > eps) {
        f = log(x) - 1;
        df = 1 / x;
        x = x - f / df;
    }
    return x;
}

double equation_pi(double eps){
    double x = 1;
    double f = 1, df;
    while (fabs(f) > eps) {
        f = cos(x) + 1;
        df = -sin(x);
        x = x - f / df;
    }
    return x;
}

double equation_ln(double eps){
    double x = 1;
    double f = 1, df;
    while (fabs(f) > eps) {
        f = exp(x) - 2;
        df = exp(x);
        x = x - f / df;
    }
    return x;
}

double equation_2(double eps){
    double x = 1;
    double f = 1, df;
    while (fabs(f) > eps) {
        f = x*x - 2;
        df = 2 * x;
        x = x - f / df;
    }
    return x;
}

bool is_prime(int number) {
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; i <= sqrt(number); i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

double equation_g(double epsilon) {
    int p = 2;
    double current = log(2) * 0.5;
    double previous;
    double product = 0.5;

    do {
        previous = current;
        do {
            p++;
        } while (!is_prime(p));

        product *= (p - 1.0) / p;
        current = log(p) * product;

    } while (fabs(previous - current) >= epsilon);

    return -log(current);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }
    double eps;
    enum status s = str_to_double(argv[1], &eps);
    if(s != SUCCESS || eps <= 0){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }
    printf("--------Limit---------\n");
    printf("e:   %.15f\n", limit_e(eps));
    printf("π:   %.15f\n", limit_pi(eps));
    printf("ln2: %.15f\n", limit_ln(eps));
    printf("√2:  %.15f\n", limit_2(eps));
    printf("Ɣ:   %.15f\n", limit_g(eps));
    printf("---------Rows---------\n");
    printf("e:   %.15f\n", rows_e(eps));
    printf("π:   %.15f\n", rows_pi(eps));
    printf("ln2: %.15f\n", rows_ln(eps));
    printf("√2:  %.15f\n", rows_2(eps));
    printf("Ɣ:   %.15f\n", rows_g(eps));
    printf("-------Equation-------\n");
    printf("e:   %.15f\n", equation_e(eps));
    printf("π:   %.15f\n", equation_pi(eps));
    printf("ln2: %.15f\n", equation_ln(eps));
    printf("√2:  %.15f\n", equation_2(eps));
    printf("Ɣ:   %.15f\n", equation_g(eps));
}
