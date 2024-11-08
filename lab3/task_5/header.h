#ifndef FUND__HEADER_H
#define FUND__HEADER_H


enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO, NOT_FOUND,
    MEMORY_ERROR, OVERFLOW
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

typedef struct {
    int id;
    char name[50];
    char surname[50];
    char group[50];
    unsigned char marks[5];
    double average_score;
}Student;

#define EPS 1e-6


enum status read_from_file(FILE* input, Student** students, int* size, int* capacity);
void print_array(Student* students, int size);
int compare_id(const void* a, const void* b);
int compare_surname(const void* a, const void* b);
int compare_name(const void* a, const void* b);
int compare_group(const void* a, const void* b);
int compare_score(const void* a, const void* b);


#endif //FUND__HEADER_H
