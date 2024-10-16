#include "header.h"

int is_valid_double(const char* str)
{
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

int is_valid_int(const char* str)
{
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


enum status str_to_double(char* str, double* result)
{
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

int is_overflow(double x, double y) {
    if (x != 0 && fabs(y) > DBL_MAX / fabs(x)) {
        return 1;
    }
    return 0;
}


enum status fast_pow(double x, int n, double* result) {
    enum status f;
    if (result == NULL) {
        return INPUT_ERROR;
    }
    if (n == 0) {
        *result = 1.0;
        return SUCCESS;
    }

    if (n < 0) {
        double temp_result;
        enum status f = fast_pow(x, -n, &temp_result);
        if (f != SUCCESS) {
            return f;
        }
        *result = 1.0 / temp_result;
        return SUCCESS;
    }

    double half_result;
    if (n & 1) {
        enum status f = fast_pow(x * x, n >> 1, &half_result);
        if (f != SUCCESS) {
            return f;
        }

        if (is_overflow(x, half_result)) {
            return OVERFLOW_ERROR;
        }

        *result = x * half_result;
    } else {

        enum status f = fast_pow(x * x, n >> 1, &half_result);
        if (f != SUCCESS) {
            return f;
        }

        *result = half_result;
    }

    return SUCCESS;
}

double geometric_mean(double* result, int count, ...)
{
    if (count <= 0){
        return INPUT_ERROR;
    }
    *result = 1;
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        double value = va_arg(args, double);
        if (value <= 0) {
            va_end(args);
            return INPUT_ERROR;
        }
        if (fabs(*result) > DBL_MAX / value) {
            va_end(args);
            return OVERFLOW_ERROR;
        }
        *result *= value;
    }
    *result = pow(*result, 1. / count);
    va_end(args);
    return SUCCESS;
}



