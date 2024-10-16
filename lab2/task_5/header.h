#ifndef FUND__HEADER_H
#define FUND__HEADER_H

#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include "string.h"
#include "float.h"
#include <stdarg.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR, OVERFLOW_ERROR
};
int oversprintf(char * str, char * format, ...);
int overfprintf(FILE * file, char * format, ...);

char* Ro(int value);
char * Zr(unsigned int value);
char * Cv(int value, int base);
char * CV (int value, int base);
enum status to(char* str, int base, int* result);
char* memoru_dump(void* input, int size);



#endif //FUND__HEADER_H
