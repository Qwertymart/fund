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
    strcpy(*result, number);
    free(number_temp);

    for (int i = 1; i < count_values; ++i)
    {
        number = va_arg(args, char*);

        if (number == NULL)
        {
            return INPUT_ERROR;
        }
         len_number = strlen(number);

        if (valid(base, number))
        {
            va_end(args);
            return INPUT_ERROR;
        }
        number_temp = strdup(number);
        if (number_temp == NULL)
        {
            va_end(args);
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

    }





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
            number[i] = (char)toupper(number[i]);
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


void sum_of_two_numbers(char ** result, char * number, int base, int *len_res, int len_numbers)
{
    int len_sum = (*len_res > len_numbers) ? len_numbers : *len_res;
    int next_digit = 0, index = 0;
    for (; index < len_sum; ++index)
    {
        int n1 = isdigit((*result)[index]) ? (*result)[index] - '0' : (*result)[index] - 'A' + 10;
        int n2 = isdigit(number[index]) ? number[index] - '0' : number[index] - 'A' + 10;
        int sum = n1 + n2  + next_digit;
        (*result)[index] = (sum % base) > 9 ? (sum % base) + 'A' - 10 : (sum % base) + '0';
        next_digit = sum / base;
    }
}
