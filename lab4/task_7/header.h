#ifndef FUND__HEADER_H
#define FUND__HEADER_H

enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO,
    MEMORY_ERROR,
    OPEN_ERROR, INVALID_BASE,
    UNINITIALIZED_VARIABLE,
    OVERFLOW_
};
#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include "string.h"
#include "float.h"
#include <stdarg.h>
#include <time.h>

typedef struct
{
    char* name;
    int value;
}MemoryCell;


void print_all_variables(MemoryCell* memoryCell, int count);
void print_variable(MemoryCell* memoryCell);
MemoryCell* find_memoryCell(MemoryCell* memoryCell, int count, char* name);
int is_number(const char* str);
enum status str_to_int(const char *str, int * result, int base);
int compare_memoryCell(const void* a, const void* b);
enum status execute_file(char* input_file_name);
enum status is_valid_name(const char* name);



#endif //FUND__HEADER_H
