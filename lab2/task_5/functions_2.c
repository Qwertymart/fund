#include "header.h"

char* Ro(int value)
{
    int sign = 1;
    if (value < 0){
        value = abs(value);
        sign = -1;
    }
    if (value == 0){
        return "N";
    }
    char *roman= (char *) malloc(sizeof(char) * 65);
    if (roman == NULL)
    {
        return NULL;
    }
    if(sign == 1){
        roman[0] = '\0';
    }
    else{
        roman[0] = '-';
        roman[1] = '\0';
    }

    int arr_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* arr_symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; ++i){
        while (value >= arr_values[i]){
            strcat(roman, arr_symbols[i]);
            value -= arr_values[i];
        }
    }
    return roman;
}

void reverse(char* str){
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {

        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}
char * Zr(unsigned int value)
{
    unsigned int arr_max_size = 16;
    unsigned int* fib = (unsigned int*)malloc(sizeof(unsigned int) * arr_max_size);
    if (fib == NULL) {
        return NULL;
    }

    fib[0] = 1;
    fib[1] = 1;
    unsigned int ind = 1;
    while(fib[ind] <= value){
        ++ind;
        if (ind >= arr_max_size){
            arr_max_size *= 2;
            unsigned int* tmp = (unsigned int*)realloc(fib, sizeof(unsigned int) * arr_max_size);
            if (tmp == NULL)
            {
                free(fib);
                return NULL;
            }
            fib = tmp;
        }
        fib[ind] = fib[ind - 1] + fib[ind -2];
    }
    char* ans = (char*)malloc(ind + 2);
    if (ans == NULL) {
        free(fib);
        return NULL;
    }

    unsigned int num = value;
    unsigned int pos = 0;


    for (int i = ind - 1; i > 0; --i) {
        if (fib[i] <= num) {
            ans[pos++] = '1';
            num -= fib[i];
        } else {
            ans[pos++] = '0';
        }
    }

    reverse(ans);


    ans[pos++] = '1';
    ans[pos] = '\0';

    free(fib);
    return ans;
}

char * Cv(int value, int base)
{
    if (base < 2 || base > 36)
    {
        base = 10;
    }

    int size_arr_res = 20;
    char *result = (char *) malloc(size_arr_res * sizeof (char));
    if (result == NULL)
    {
        return  NULL;

    }

    int i = 0;
    int sign = 0;
    char *arr_base = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (value < 0){
        value *= -1;
        result[0] = '-';
        ++i;
        sign = 1;
    }

    while(value > 0)
    {
        int temp = value % base;
        value /= base;
        result[i++] = (char)arr_base[temp];
        if (i == size_arr_res)
        {
            size_arr_res *= 2;
            char *temp_result = (char *) realloc(result, size_arr_res);
            if (temp_result == NULL)
            {
                free(result);
                return NULL;
            }
            result = temp_result;
        }
    }
    int start = sign;
    int end = i - 1;
    while(start < end)
    {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }
    result[i] = '\0';
    return result;
}

char * CV (int value, int base)
{
    char *result = Cv(value, base);
    for (int i = 0; i < strlen(result); ++i){
        result[i] = toupper(result[i]);
    }
    return result;
}

enum status to(char* str, int base, int * result)
{
    if(base <  2 || base > 36)
    {
        base = 10;
    }
    *result = 0;
    int len = strlen(str);
    int sign = 1;
    int start = 0;

    if(str[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start ; i < len; ++i)
    {
        int digit;
        if (isdigit(str[i]))
        {
            digit = str[i] - '0';
        } else if (isalpha(str[i])) {
            digit = tolower(str[i]) - 'a' + 10;
        } else {
            return INPUT_ERROR;
        }
        if (digit >= base)
        {
            return INPUT_ERROR;
        }
        *result = *result * base + digit;
    }
    *result *= sign;
    return SUCCESS;
}

char* memoru_dump(void* input, int size)
{
    char *res = (char *) malloc(sizeof (char) * size * 10);
    if (res == NULL)
    {
        return NULL;
    }

    int sz = 0;
    char *pt = (char *) input;
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            char bit = (((*(pt + i)) >> j) & 1) == 0 ? '0' : '1';
            res[sz++] = bit;
        }
        res[sz++] = ' ';
    }
    sz--;
    res[sz] = '\0';
    return res;
}
