#include "header.h"

int main(int argc, char* argv[]){
    int count_values = argc - 2;
    char flag = argv[1][0];
    if (flag != '2' && flag != '1'){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }

    switch (flag) {
        case '1': {
            if (argc != 2) {
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            double result;
            enum status f = geometric_mean(&result, 3, 5.0, 5.0, 5.0);
            if (f == OVERFLOW_ERROR) {
                printf("Ошибка: переполнение\n");
                return INPUT_ERROR;
            }
            if (f == INPUT_ERROR) {
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            printf("%lf \n", result);
            break;
        }

        case '2':{
            double value;
            if (str_to_double(argv[2], &value) != SUCCESS){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            int degree;
            if (str_to_int(argv[3], &degree) != SUCCESS){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            double result = value;
            enum status res = fast_pow(value, degree, &result);
            if (res == SUCCESS) {
                printf("Результат: %lf\n", result);
            } else if (res == OVERFLOW_ERROR) {
                printf("Ошибка: переполнение\n");
            } else {
                printf("Ошибка: некорректный ввод\n");
            }

            break;
        }
    }
}