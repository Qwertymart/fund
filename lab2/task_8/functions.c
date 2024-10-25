#include "header.h"



enum status sum(char ** result, int base, int count_values, ...)
{
    if (count_values <= 0 || base < 2 || base > 36)
    {
        return INPUT_ERROR;
    }

    va_list args;
    va_start(args, count_values);
    char* number = va_arg(args, char*);

    if (number == NULL)
    {
        va_end(args);
        return INPUT_ERROR;
    }
    int len_number = strlen(number);


    if (valid(base, number))
    {
        va_end(args);
        return INPUT_ERROR;
    }
    char * number_temp = strdup(number);
    if (number_temp == NULL)
    {
        va_end(args);
        return MEMORY_ERROR;

    }
    reverse(&number_temp, len_number);
    int capacity_res = len_number * 2;
    int len_res = len_number;


    *result = (char *)calloc(sizeof(char), capacity_res);
    if((*result) == NULL)
    {
        va_end(args);
        free(number_temp);
        return MEMORY_ERROR;
    }
    strcpy(*result, number_temp);
    free(number_temp);

    for (int i = 0; i < count_values - 1; ++i)
    {
        number = va_arg(args, char*);

        if (number == NULL)
        {
            free((*result));
            va_end(args);
            return INPUT_ERROR;
        }
         len_number = strlen(number);

        if (valid(base, number))
        {
            free((*result));
            va_end(args);
            return INPUT_ERROR;
        }
        number_temp = strdup(number);
        if (number_temp == NULL)
        {
            va_end(args);
            free((*result));
            return MEMORY_ERROR;

        }
        reverse(&number_temp, len_number);

        if (len_number + 1 > capacity_res || len_res + 1 > capacity_res)
        {
            int max = len_res > len_number ? len_res : len_number;
            capacity_res = max * 2;
            char * for_realloc = (char *)realloc((*result), capacity_res * sizeof(char));
            if(for_realloc == NULL)
            {
                va_end(args);
                free(number_temp);
                return MEMORY_ERROR;
            }
            (*result) = for_realloc;
        }
        sum_of_two_numbers(result, number_temp, base, &len_res, len_number);
        free(number_temp);
    }
    while (len_res > 1 && (*result)[len_res - 1] == '\0')
    {
        (*result)[--len_res] = '\0';
    }
    reverse(result, len_res);
    va_end(args);
    return SUCCESS;

}


int valid(int base, char * number)
{
    if (number[0] == '\0')
    {
        return 1;
    }

    for (int i = 0; number[i] != '\0'; ++i)
    {
        if(isalpha(number[i]))
        {
            if(number[i] >= 'a' && number[i] <= 'z')
            {
                return 0;
            }
            if(number[i]  - 'A' + 10 >= base)
            {
                return 1;
            }
        }
        else if (isdigit(number[i]))
        {
            if(number[i] - '0'>= base)
            {
                return 1;
            }
        }
        else {
            return 1;
        }
    }
    return 0;
}

void reverse(char ** number, int len)
{
    int i = 0, j = len - 1;
    for(; (j - i) > 0; ++i, --j)
    {
        char temp = (*number)[i];
        (*number)[i] = (*number)[j];
        (*number)[j] = temp;
    }
}


void sum_of_two_numbers(char **result, char *number, int base, int *len_res, int len_number) {
    int max_len = (*len_res > len_number) ? *len_res : len_number;
    int carry = 0, i;

    for (i = 0; i < max_len || carry; ++i) {
        if (i >= *len_res) {
            (*result)[i] = '0';
            (*len_res)++;
        }

        int n1 = isdigit((*result)[i]) ? (*result)[i] - '0' : (*result)[i] - 'A' + 10;
        int n2 = (i < len_number) ? (isdigit(number[i]) ? number[i] - '0' : number[i] - 'A' + 10) : 0;
        int sum = n1 + n2 + carry;

        (*result)[i] = (sum % base) < 10 ? (sum % base) + '0' : (sum % base) + 'A' - 10;
        carry = sum / base;
    }

    (*result)[i] = '\0';
    *len_res = i;
}
