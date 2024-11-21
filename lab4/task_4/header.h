#ifndef FUND__HEADER_H
#define FUND__HEADER_H

typedef struct
{
    int value;
    int init;
} Variable;

enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO,
    MEMORY_ERROR, OVERFLOW,
    OPEN_ERROR, INVALID_BASE,
    UNINITIALIZED_VARIABLE
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

enum status execute_file(char* input_file_name, Variable * variables);
enum status str_to_int(const char *str, int * result, int base);
enum status read_variable(char variable, const int* base, Variable * variables);
enum status write_variable(char variable, const int* base, Variable* variables);
enum status assigment_variable(char* instruction, Variable* variables );
enum status process_instruction(char* instruction, Variable * variables);
enum status remove_comments(FILE* input, FILE* output);

enum status process_instruction_trace(char* instruction, Variable * variables, FILE* trace);
enum status read_variable_trace(char variable, const int* base, Variable * variables, FILE* trace);
enum status write_variable_trace(char variable, const int* base, Variable* variables, FILE* trace);
enum status assigment_variable_trace(char* instruction, Variable* variables, FILE* trace);
enum status execute_file_trace(char* input_file_name, Variable * variables, char* trace_name);

#endif //FUND__HEADER_H
