#include "header.h"

int Ro(char* str, int* index_plus, char format_end)
{
    int result = 0;
    int len = strlen(str);

    for (int i = 0; str[i] != format_end && str[i] != '\0'; ++i)
    {
        if (str[i] == 'M') result += 1000;
        else if (str[i] == 'D') result += 500;
        else if (str[i] == 'C') {
            if (i + 1 < len && (str[i + 1] == 'D' || str[i + 1] == 'M'))
                result -= 100; // CD = 400, CM = 900
            else
                result += 100;
        }
        else if (str[i] == 'L') result += 50;
        else if (str[i] == 'X') {
            if (i + 1 < len && (str[i + 1] == 'L' || str[i + 1] == 'C'))
                result -= 10; // XL = 40, XC = 90
            else
                result += 10;
        }
        else if (str[i] == 'V') result += 5;
        else if (str[i] == 'I') {
            if (i + 1 < len && (str[i + 1] == 'V' || str[i + 1] == 'X'))
                result -= 1; // IV = 4, IX = 9
            else
                result += 1;
        }
        ++(*index_plus);
    }
    return result;
}

int Zr(char* str, char format_end, int* index_plus) {
    int result = 0;
    int previous_1 = 1;
    int previous_2 = 2;
    int fib_value = 2;

    for (int i = 0; str[i] != format_end && str[i] != '\0'; ++i) {

        if (str[i] == '1') {
            if (!(str[i + 1] == format_end || str[i + 1] == '\0')) {

                if (i == 0 || i == 1) {
                    result += i + 1;
                } else {
                    result += fib_value;
                    int temp = previous_2;
                    previous_2 = previous_1 + previous_2;
                    previous_1 = temp;

                    fib_value = previous_2;

                }
                printf("%d   %d\n", i, result);
            }
        }
        else{
            int temp = previous_2;
            previous_2 = previous_1 + previous_2;
            previous_1 = temp;

            fib_value = previous_2;
        }


        ++(*index_plus);
    }

    return result;
}


enum status str_to_int(const char *str, int * result, int base)
{
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

enum status Cv(char* str, char format_end, int base, int *result, int* index_plus)
{
    if (base < 2 || base > 36)
    {
        base = 10;
    }

    char *arr = (char *) malloc(sizeof(char) * 11);
    if (arr == NULL)
    {
        return INPUT_ERROR;
    }
    int i = 0;
    for(; str[i] != format_end && str[i] != '\0'; ++i)
    {
        arr[i] = str[i];
        ++(*index_plus);
    }
    arr[++i] = '\0';

    enum status f = str_to_int(arr, result, base);
    free(arr);
    return f;
}