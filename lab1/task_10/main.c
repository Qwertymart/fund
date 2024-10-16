#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef long int li;

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

int is_valid_int(const char* str, int base) {
    if (*str == '-' || *str == '+') str++;

    for (const char* p = str; *p; p++) {
        if (!isalnum(*p)) {
            return 0;
        }
        if (isdigit(*p)) {
            if ((*p - '0') >= base) {
                return 0;
            }
        }
        else if (*p >= 'a' && *p <= 'z'){
            return 0;
        }
        else if (isalpha(*p)) {
            int val = toupper(*p) - 'A' + 10;
            if (val >= base) {
                return 0;
            }
        }
    }

    return 1;
}

enum status str_to_int(const char *str, int * result, int base)
{
    if (!(is_valid_int(str, base))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return INPUT_ERROR;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, base);

    if (temp < INT_MIN || temp > INT_MAX) {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

void int_to_base_str(int num, int base, char *str) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buf[50];
    int i = 0, sign = 0;
    if (num < 0) {
        sign = 1;
        num = -num;
    }
    if (num == 0) {
        strcpy(str, "0");
        return;
    }
    while (num > 0) {
        buf[i++] = digits[num % base];
        num /= base;
    }
    if (sign) {
        buf[i++] = '-';
    }
    buf[i] = '\0';

    int len = strlen(buf);
    for (int j = 0; j < len; j++) {
        str[j] = buf[len - j - 1];
    }
    str[len] = '\0';
}


int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    int base = 0;
    enum status f1 = str_to_int(argv[1], &base, 10);
    if (f1 == INPUT_ERROR){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    if (base > 36 || base < 2){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    if (strcmp(argv[argc - 1], "Stop") != 0){
        printf("Ошибка: вы забыли Stop\n");
        return INPUT_ERROR;
    }
    int max = 0;
    char* max_str = NULL;
    for (int i = 2; i < argc; ++i){
        if (strcmp(argv[i], "Stop") == 0){
            break;
        }
        int temp = 0;
        enum status f2 = str_to_int(argv[i], &temp, base);
        if (f2 == INPUT_ERROR){
            printf("Ошибка: некорректный ввод\n");
            return INPUT_ERROR;
        }
        if (abs(temp) > abs(max)){
            max = temp;
            max_str = argv[i];
        }

    }
    if (max_str == NULL) {
        printf("Ошибка: не было введено ни одного числа перед \"Stop\"\n");
        return INPUT_ERROR;
    }

    printf("Максимальное по модулю число в исходной системе счисления: %s\n", max_str);
    printf("Максимальное по модулю число в десятичной системе счисления: %d\n", max);
    char str9[50], str18[50], str27[50], str36[50];

    int_to_base_str(max, 9, str9);
    int_to_base_str(max, 18, str18);
    int_to_base_str(max, 27, str27);
    int_to_base_str(max, 36, str36);

    printf("В системе счисления с основанием 9: %s\n", str9);
    printf("В системе счисления с основанием 18: %s\n", str18);
    printf("В системе счисления с основанием 27: %s\n", str27);
    printf("В системе счисления с основанием 36: %s\n", str36);
}
