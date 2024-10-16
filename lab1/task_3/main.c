#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include <ctype.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, NOT_FOUND,
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

int is_valid_int(const char* str) {

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '-' && *p != '+') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_int(const char *str, int * result)
{
    if (!(is_valid_int(str))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return INPUT_ERROR;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, 10);

    if (temp < INT_MIN || temp > INT_MAX) {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
    return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
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


enum status func_q(double a, double b, double c, double eps){
    double discr = b*b - 4*a*c;

    if (fabs(discr) < eps){
        discr = 0.0;
    }
    if ((a == 0 && b == 0 && c == 0)){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет бесконечное множество решений.\n", a, b, c);
        return SUCCESS;
    }
    if (a == 0 && b != 0 && c != 0){
        double x = -c/b;
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет один корень: x = %.2f\n", a, b, c, x);
        return SUCCESS;
    }
    if (a != 0 && b == 0 && c != 0){
        if (c * a > 0){
            printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 не имеет вещественных корней.\n", a, b, c);
            return SUCCESS;
        }
        else{
            double x1 = sqrt(-(c/a));
            double x2 = -sqrt(-(c/a));
            printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет два корня: x1 = %.2f, x2 = %.2f\n", a, b, c, x1, x2);
            return SUCCESS;

        }
    }
    if (a == 0 && b == 0 && c != 0){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 не имеет вещественных корней.\n", a, b, c);
        return SUCCESS;
    }
    if (a == 0 && b != 0 && c == 0){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет один корень: x = %.2f\n", a, b, c, 0.0);
        return SUCCESS;
    }
    if (a != 0 && b == 0 && c == 0){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет один корень: x = %.2f\n", a, b, c, 0.0);
        return SUCCESS;
    }
    if (discr < 0){
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 не имеет вещественных корней.\n", a, b, c);
        return SUCCESS;
    }
    if (discr == 0) {
        double x = -b / (2 * a);
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет один корень: x = %.2f\n", a, b, c, x);
        return SUCCESS;
    } else {
        double sqrt_d = sqrt(discr);
        double x1 = (-b + sqrt_d) / (2 * a);
        double x2 = (-b - sqrt_d) / (2 * a);
        if (x1 == 0.0) x1 = 0;
        if (x2 == 0.0) x2 = 0;
        printf("Уравнение %.2fx^2 + %.2fx + %.2f = 0 имеет два корня: x1 = %.2f, x2 = %.2f\n", a, b, c, x1, x2);
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
                printf("Ошибка: некорректный ввод\n");
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
            if (eps <= 0){
                printf("Ошибка: некорректный ввод");
                return INPUT_ERROR;
            }
            double arr[3] = {a, b, c};
            int l = 0, r = 2;
            permute(arr, l, r, eps);
            break;
        }
        case 'm':{
            if (argc != 4) {
                printf("Ошибка: для операции 'm' необходимо 4 аргумента.\n");
                return INPUT_ERROR;
            }
            int a, b;
            enum status f1 = str_to_int(argv[2], &a);
            enum status f2 = str_to_int(argv[3], &b);
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
            if (f1 == INPUT_ERROR || f2 == INPUT_ERROR || f3 == INPUT_ERROR || f4 == INPUT_ERROR ||
                a == HUGE_VAL || a == -HUGE_VAL || b == HUGE_VAL || b == -HUGE_VAL || c == HUGE_VAL || c == -HUGE_VAL) {
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
    return 0;
}