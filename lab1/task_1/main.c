#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "limits.h"
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS, 
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR
};

enum status func_h(li x){
    li found = 0;
    if (x == 0) {
        return DIVISION_BY_ZERO;
    }
    for(int i = 1; i <= 100; ++i){
        if(i % x == 0){
            found = 1;
            printf("%d ", i);
        }
    }
    if (found == 0) {
        return NOT_FOUND;
    } else {
        return SUCCESS;
    }
}

enum status func_p(li x, li* num_of_found){
    if(x == 0){
        return DIVISION_BY_ZERO;
    }
    if (x == 1){
        return INPUT_ERROR;
    }
    for (int i = 2; i <= sqrt(x); ++i){
        if (x % i == 0){
            *num_of_found = 1;
            return SUCCESS;
        }
    }
    return SUCCESS;


}

enum status func_s(li x, char* result, size_t size){
    if (x < 0){
        return NOT_FOUND;
    }
    if (result == NULL){
        return INPUT_ERROR;
    }
    int written = snprintf(result, size, "%lX", x);
    if (written >= size) {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

enum status func_e(li x, li*** table, size_t* rows, size_t* cols) {
    if (x < 0 || x > 10) {
        return INPUT_ERROR;
    }
    *rows = 10;
    *cols = x;

    *table = (li**) malloc(*rows * sizeof (li*));
    if (*table == NULL){
        return MEMORY_ERROR;
    }
    for(size_t i = 0; i < *rows; ++i){
        (*table)[i] = (li*) malloc(((*cols)*sizeof(li)));//размер строки в 16 символов
        if ((*table)[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free((*table)[j]);
            }
            free(*table);
            return MEMORY_ERROR;
        }
    }
    for (size_t base = 1; base <= 10; ++base) {
        for (size_t i = 1; i <= x; ++i) {
            (*table)[base - 1][i - 1] = pow(base, i);
        }
    }
    return SUCCESS;
}

enum status func_a(li x, li* sum){
    if (x < 0){
        return INPUT_ERROR;
    }
    *sum = (x * (x + 1)) / 2;
    return SUCCESS;
}

enum status func_f(li x, li* result){
    if(x<0){
        return INPUT_ERROR;
    }
    *result = 1;
    for(li i = 2; i <= x; ++i){
        if (*result > LONG_MAX / i) {
            return MEMORY_ERROR;
        }
        *result *= i;
    }
    return SUCCESS;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }
    char *end_number;
    li x = strtol(argv[1], &end_number, 10);

    if (*end_number != '\0'){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }
    printf("Число: %ld\n", x);

    char flag = argv[2][1];
    if (argv[2][0] != '-' && argv[2][0] != '/') {
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }

    switch(flag) {
        case 'h': {
            li found = 0;
            enum status f = func_h(x);
            if (f == DIVISION_BY_ZERO) {
                printf("Ошибка: деление на ноль невозможно.\n");
            }
            else if (f == NOT_FOUND) {
                printf("Нет кратных чисел в пределах 100.\n");
            }
            else if(f == SUCCESS){
                printf("\n");
            }
            break;
        }

        case 'p':{
            li num_of_found = 0;
            enum status f = func_p(x, &num_of_found);
            if (f == INPUT_ERROR){
                printf("Не простое, не составное\n");
                break;
            }
            if (f == SUCCESS){
                if(num_of_found == 1){
                    printf("Число составное\n");
                }
                else{
                    printf("Число простое\n");
                }
            }
            else if(f == DIVISION_BY_ZERO){
                printf("Ошибка: деление на ноль невозможно.\n");
            }
            break;
        }
        case 's':{
            size_t size = 17;
            char *result = (char *)malloc(size*sizeof(char));
            if (result == NULL) {
                printf("Ошибка выделения памяти.\n");
                return MEMORY_ERROR;
            }
            enum status f = func_s(x, result, size);
            if (f == SUCCESS) {
                for (int i = 0; i < strlen(result); ++i){
                    printf("%c ", result[i]);
                }
                printf("\n");
            }
            else if (f == INPUT_ERROR){
                printf("Ошибка: преобразование в шестнадцатеричный формат не удалось.\n");
            }
            else if(f == NOT_FOUND){
                printf("Ошибка: отрицательное число");
            }
            free(result);
            break;
        }

        case 'e':{
            size_t rows, cols;
            li** table = NULL;

            enum status f = func_e(x, &table, &rows, &cols);
            if (f == INPUT_ERROR) {
                printf("Ошибка: значение x должно быть от 1 до 10.\n");
            }

            else if (f == MEMORY_ERROR){
                printf("Ошибка выделения памяти");
            }

            else if (f == SUCCESS) {
                for (size_t i = 0; i < rows; ++i) {
                    printf("Основание %zu: ", i + 1);
                    for (size_t j = 0; j < cols; ++j) {
                        printf("%ld ", table[i][j]);
                    }
                    printf("\n");
                }
            }
            break;
        }
        case 'a':{
            li sum = 0;
            enum status f = func_a(x, &sum);
            if (f == INPUT_ERROR) {
                printf("Ошибка: значение x должно быть от 1 до 10.\n");
            }
            else if (f == SUCCESS){
                printf("Сумма: %ld\n", sum);
            }
            break;
        }

        case 'f':{
            li result = 1;
            enum status f = func_f(x, &result);

            if (f == INPUT_ERROR){
                printf("Ошибка: введено некорректно.\n");
            }

            if (f == MEMORY_ERROR){
                printf("Ошибка: слишком большое число.\n");
            }
            else if (f == SUCCESS){
                printf("Факториал %ld: %ld\n", x, result);
            }
            break;
        }

        default:
            printf("Неизвестный флаг\n");
            break;
    }
    return 0;
}