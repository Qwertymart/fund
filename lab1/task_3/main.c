#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR
};

enum status str_to_int(const char *str, long int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
    {
        return INPUT_ERROR;
    } else if (errno != 0 && *result == 0) {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }

    return SUCCESS;
}

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

enum status func_q(double a, double b, double c, double eps){
    double discr = b*b - 4*a*c;

    if (fabs(discr) < eps){
        discr = 0.0;
    }
    if ((a == 0 && b == 0 && c == 0)){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет бесконечное множество решений.\n", a, b, c);
        return SUCCESS;
    }
    if (discr < 0){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 не имеет вещественных корней.\n", a, b, c);
        return SUCCESS;
    }
    if (discr == 0) {
        double x = -b / (2 * a);
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет один корень: x = %.6f\n", a, b, c, x);
        return SUCCESS;
    } else {
        double sqrt_d = sqrt(discr);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет два корня: x1 = %.6f, x2 = %.6f\n", a, b, c, x1, x2);
        return SUCCESS;
    }
}

void permute(double arr[], int l, int r, double eps){
    if (l==r){
        enum status f = func_q(arr[0], arr[1], arr[2], eps);

    }else{
        for(int i = l; i <= r; ++i){
            double temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
            permute(arr, l + 1, r, eps);
            temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
        }
    }
}

enum status func_m(li a, li b){
    if (b == 0){
        return DIVISION_BY_ZERO;
    }
    if (a == 0){
        printf("%ld не кратно %ld\n", a, b);
        return SUCCESS;
    }
    if(a % b == 0){
        printf("%ld кратно %ld\n", a, b);
    }else{
        printf("%ld не кратно %ld\n", a, b);
    }
    return SUCCESS;
}

void sort(double* arr){
    double min = -HUGE_VAL;
    int n = 3;
    while (n > 0){
        for (int i = 0; i < 2; ++i){
            if (arr[i] < arr[i + 1]){
                double temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
            --n;
        }
    }
}

enum status func_t(double arr[], double eps) {
    if (arr[2] == 0){
        printf("Числа: %f, %f, %f НЕ могут быть сторонами прямоугольного треугольника\n", arr[0], arr[1], arr[2]);
        return INPUT_ERROR;
    }
    if (fabs(arr[0] * arr[0] - (arr[1] * arr[1] + arr[2] * arr[2])) < eps) {
        printf("Числа: %f, %f, %f могут быть сторонами прямоугольного треугольника\n", arr[0], arr[1], arr[2]);
    } else {
        printf("Числа: %f, %f, %f НЕ могут быть сторонами прямоугольного треугольника\n", arr[0], arr[1], arr[2]);
    }
    return SUCCESS;
}


int main(int argc, char* argv[]){
    if (argv[1][0] != '-' && argv[1][1] != 'q') {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    switch (argv[1][1]) {
        case 'q':{
            if (argc != 6){
                printf("Ошибка: некорректный ввод");
                return INPUT_ERROR;
            }
            double a,b,c,eps;
            enum status f1 = str_to_double(argv[2], &eps);
            enum status f2 = str_to_double(argv[3], &a);
            enum status f3 = str_to_double(argv[4], &b);
            enum status f4 = str_to_double(argv[5], &c);
            if (f1 == INPUT_ERROR || f2 == INPUT_ERROR || f3 == INPUT_ERROR || f4 == INPUT_ERROR){
                printf("Ошибка: некорректный ввод");
                return INPUT_ERROR;
            }
            double arr[3] = {a, b, c};
            int l = 0, r = 2;
            permute(arr, l, r, eps);
        }
        case 'm':{
            if (argc != 4) {
                printf("Ошибка: для операции 'm' необходимо 4 аргумента.\n");
                return INPUT_ERROR;
            }
            li a, b;
            enum status f1 = str_to_int(argv[2], &a, 10);
            enum status f2 = str_to_int(argv[3], &b, 10);
            if (f1 == INPUT_ERROR || f2 == INPUT_ERROR) {
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            enum status f = func_m(a, b);
            if (f != SUCCESS){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            break;
        }
        case 't':{
            if (argc != 6) {
                printf("Ошибка: для операции 't' необходимо 6 аргументов.\n");
                return INPUT_ERROR;
            }
            double a,b,c,eps;
            enum status f1 = str_to_double(argv[2], &eps);
            enum status f2 = str_to_double(argv[3], &a);
            enum status f3 = str_to_double(argv[4], &b);
            enum status f4 = str_to_double(argv[5], &c);
            if (f1 == INPUT_ERROR || f2 == INPUT_ERROR || f3 == INPUT_ERROR || f4 == INPUT_ERROR){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }

            double arr[3] = {a, b, c};
            sort(arr);
            enum status f = func_t(arr, eps);
            if (f != SUCCESS){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            break;
        }
        default:
            printf("Ошибка: такого флага нет в доступных флагах: %s\n", argv[1]);
            return INPUT_ERROR;
    }

}
