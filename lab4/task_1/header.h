#ifndef FUND__HEADER_H
#define FUND__HEADER_H

enum status{
    SUCCESS, INPUT_ERROR,
    DIVISION_BY_ZERO,
    MEMORY_ERROR, OVERFLOW,
    OPEN_ERROR
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

typedef struct Macro
{
    int hash;
    char* key;
    char* value;
    struct Macro* next;
} Macro;

typedef struct Hash_table
{
    Macro** table;
    int size;
    int count;
} Hash_table;

#define SIZE_TABLE 128

int calculate_hash(const char* key, int size);
Hash_table* create_table(int size);
enum status insert_item(Hash_table* table, const char* key, const char* value);
char* search_item(Hash_table* table, const char* key);
void free_table(Hash_table * table);
void print_hash_table(Hash_table* table);
enum status read_file(FILE* file, Hash_table* table);
enum status write_to_file(Hash_table* table, FILE* input, FILE* output);
enum status check_and_rebuild_table(Hash_table* table);


#endif //FUND__HEADER_H
