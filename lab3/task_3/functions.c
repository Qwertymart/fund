#include "header.h"

int is_valid_double(const char* str) {
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

int is_valid_int(const char* str) {

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
        return OVERFLOW;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, 10);

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

enum status str_to_double(char* str, double* result){

    if (!(is_valid_double(str))){
        return INPUT_ERROR;
    }
    if (strlen(str) > 17)
    {
        return OVERFLOW;
    }
    char *endptr;
    *result = strtod(str, &endptr);
    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

int cmp_a(const void* a, const void* b)
{
    const Employee * emp_1 = (const Employee*)a;
    const Employee* emp_2 = (const Employee*)b;

    if (emp_1->salary < emp_2->salary)
    {
        return -1;
    }
    if (emp_1->salary > emp_2->salary)
    {
        return 1;
    }
    int surname_cmp = strcmp(emp_1->surname, emp_2->surname);
    if (surname_cmp != 0)
    {
        return surname_cmp;
    }
    int name_cmp = strcmp(emp_1->name, emp_2->name);
    if(name_cmp != 0)
    {
        return name_cmp;
    }
    return emp_1->id - emp_2->id;
}


int cmp_d(const void* a, const void* b)
{
    const Employee * emp_1 = (const Employee*)b;
    const Employee* emp_2 = (const Employee*)a;

    if (emp_1->salary < emp_2->salary)
    {
        return -1;
    }
    if (emp_1->salary > emp_2->salary)
    {
        return 1;
    }
    int surname_cmp = strcmp(emp_1->surname, emp_2->surname);
    if (surname_cmp != 0)
    {
        return surname_cmp;
    }
    int name_cmp = strcmp(emp_1->name, emp_2->name);
    if(name_cmp != 0)
    {
        return name_cmp;
    }
    return emp_1->id - emp_2->id;
}
