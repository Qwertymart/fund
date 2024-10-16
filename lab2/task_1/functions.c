#include "header.h"

int str_len(char const * str){
    const char *end = str;
    while(*end++ != '\0');
    return end - str - 1;
}

enum status reverse_str(char* str, char ** result){
    if (str == NULL){
        return INPUT_ERROR;
    }
    int len = str_len(str);
    *result = (char*)malloc((len + 1) * sizeof(char));
    if (*result == NULL) {
        return MEMORY_ERROR;
    }
    for (int i = 0; i < len; ++i){
        (*result)[i] = str[len - i - 1];
    }

    (*result)[len] = '\0';
    return SUCCESS;
}

enum status odd_upper(char* str, char ** result){
    if (str == NULL){
        return INPUT_ERROR;
    }
    int len = str_len(str);
    *result = (char*)malloc((len + 1) * sizeof(char));
    if (*result == NULL) {
        return MEMORY_ERROR;
    }
    for (int i = 0; i < len; ++i){
        if (i % 2 != 0){
            (*result)[i] = toupper(str[i]);
        }
        else{
            (*result)[i] = str[i];
        }
    }
    (*result)[len] = '\0';
    return SUCCESS;
}

enum status string_in_order(char* str, char ** result){
    if (str == NULL){
        return INPUT_ERROR;
    }
    int len = str_len(str);
    *result = (char*)malloc((len + 1) * sizeof(char));
    if (*result == NULL) {
        return MEMORY_ERROR;
    }
    int index = 0;
    for( int i = 0; i < len; ++i){
        if (str[i] >= '0' && str[i] <= '9'){
            (*result)[index++] = str[i];
        }
    }
    for( int i = 0; i < len; ++i) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            (*result)[index++] = str[i];
        }
    }
    for( int i = 0; i < len; ++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z')
        || (str[i] >= 'A' && str[i] <= 'Z')
        || (str[i] >= '0' && str[i] <= '9'))) {
            (*result)[index++] = str[i];
        }
    }
    (*result)[index] = '\0';
    return SUCCESS;
}

int is_valid_int(const char* str) {

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '-' && *p != '+') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_int(const char *str, unsigned int * result)
{
    if (!(is_valid_int(str))){
        return INPUT_ERROR;
    }
    size_t len = str_len(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return INPUT_ERROR;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, 10);

    if(temp < 0){
        return INPUT_ERROR;
    }
    if (temp > INT_MAX) {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (unsigned int)temp;
    return SUCCESS;
}

void swap(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}

enum status concatenation(char ** strs, int count, char ** result, unsigned int seed){
    int len = 0;
    for(int i = 0; i < count; ++i)
    {
        len += str_len(strs[i]);
    }
    (*result) = (char *)malloc(sizeof(char) * (len + 1));
    if((*result) == NULL)
    {
        return MEMORY_ERROR;
    }
    int rand_num;
    srand(seed);
    for(int i = 0; i < count; ++i)
    {
        rand_num = rand() % count;
        swap(&strs[i], &strs[rand_num]);
    }
    int index = 0;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; strs[i][j] != '\0'; ++j) {
            (*result)[index++] = strs[i][j];
        }
    }
    (*result)[index] = '\0';
    return SUCCESS;
}

