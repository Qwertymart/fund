#include "header.h"


int is_valid_digit(char ch, int base) {
    if (isdigit(ch)) {
        return (ch - '0') < base;
    } else if (isalpha(ch)) {
        ch = tolower(ch);
        return (ch - 'a' + 10) < base;
    }
    return 0;
}

int is_valid_int(const char* str, int base) {
    if (*str == '-' || *str == '+') {
        str++;
    }

    for (const char* p = str; *p; p++) {
        if (!is_valid_digit(*p, base)) {
            return 0;
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
        return OVERFLOW;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, base);

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}