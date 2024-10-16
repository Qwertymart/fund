#ifndef FUND__HEADER_H
#define FUND__HEADER_H


#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

int str_len(char const * str);
enum status reverse_str(char * str, char ** result);
enum status odd_upper(char* str, char ** result);
enum status string_in_order(char* str, char ** result);
enum status str_to_int(const char *str, unsigned int * result);
int is_valid_int(const char* str);
enum status concatenation(char ** strs, int count, char ** result , unsigned int seed);

#endif //FUND__HEADER_H
