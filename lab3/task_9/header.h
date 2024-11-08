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

typedef struct Node
{
    char* word;
    int count;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct
{
    char* word;
    int count;
} Word_frequency;

enum status read_file(FILE* file, Node** root, const char* sep);
Node* free_tree(Node* root);
int find_word_frequency(Node* root, char* word);
int count_nodes(Node* root);
int compare_freqeuncy(const void* a, const void* b);
void fill_array_from_tree(Node* root, Word_frequency ** array, int* index);
void print_top_n(Node* root, int n);
void find_min_max_words(Node* root, Node** min_node, Node** max_node);
void print_min_max_words(Node* root);
int find_tree_depth(Node* root);
void save_tree_to_file(Node* root, FILE* file);
Node* restore_tree(Node* root, FILE* file);
Node* search_node(Node* root, char* word);
Node* insert_node(Node* root, char* word);
Node* create_node(const char* word);

enum status str_to_int(const char *str, int * result);

#endif //FUND__HEADER_H
