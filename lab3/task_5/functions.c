#include "header.h"

enum status valid_string(char* str)
{
    int len = strlen(str);
    if (len > 49)
    {
        return INPUT_ERROR;
    }
    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return INPUT_ERROR;
    }
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

enum status validate_id(char* id, int *id_res)
{
    if (str_to_int(id, id_res) != SUCCESS || id < 0)
    {
        return INPUT_ERROR;
    }
    return SUCCESS;
}

enum status read_from_file(FILE* input, Student** students, int* size, int* capacity)
{
    *size = 0;
    *capacity = 10;
    *students = (Student *) malloc(*capacity * sizeof(Student));
    if (*students == NULL)
    {
        return MEMORY_ERROR;
    }
    int check;
    char id[15];
    while ((check = fscanf(input, "%15s %49s %49s %49s %c %c %c %c %c",
                           id, (*students)[*size].name,
                           (*students)[*size].surname, (*students)[*size].group,
                           &(*students)[*size].marks[0], &(*students)[*size].marks[1],
                           &(*students)[*size].marks[2], &(*students)[*size].marks[3],
                           &(*students)[*size].marks[4])) == 9)
    {
        enum status f = validate_id(id, &(*students)[*size].id);
        if (f != SUCCESS)
        {
            return INPUT_ERROR;
        }
        if (((*students)[*size].id < 0))
        {
            free(*students);
            return INPUT_ERROR;
        }
        for (int i = 0; i < (*size); ++i)
        {
            if ((*students)[i].id == (*students)[*size].id)
            {
                free(*students);
                return INPUT_ERROR;
            }
        }
        if(valid_string((*students)[*size].name) == INPUT_ERROR)
        {
            free(*students);
            return INPUT_ERROR;
        }
        if (valid_string((*students)[*size].surname) == INPUT_ERROR)
        {
            free(*students);
            return INPUT_ERROR;
        }
        (*students)[*size].average_score = 0;
        for (int i = 0; i < 5; ++i)
        {
            unsigned char mark = (*students)[*size].marks[i];
            if(!(mark >= '2' && mark <= '5'))
            {
                free(*students);
                return INPUT_ERROR;
            }
            (*students)[*size].average_score += (mark - '0');
        }
        (*students)[*size].average_score /= 5;
        ++(*size);
        if (*capacity <= *size)
        {
            *capacity *= 2;
            Student *for_realloc = (Student *)realloc(*students, *capacity * sizeof(Student));
            if (for_realloc == NULL)
            {
                free(*students);
                return INPUT_ERROR;
            }
            *students = for_realloc;
        }
    }

    if (check < 9 && check != EOF)
    {
        free(*students);
        return INPUT_ERROR;
    }
    return SUCCESS;
}

void print_array(Student* students, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("ID: %d %s %s %s ", students[i].id,
               students[i].name, students[i].surname,
               students[i].group);
        for (int j = 0; j < 5; ++j)
        {
            printf("%c ", students[i].marks[j]);
        }
        printf("\n%lf\n", students[i].average_score);
    }
}

int compare_id(const void* a, const void* b)
{
    const Student* student_1 = (const Student*)a;
    const Student* student_2 = (const Student*)b;
    return student_1->id - student_2->id;
}

int compare_surname(const void* a, const void* b)
{
    const Student* student_1 = (const Student*)a;
    const Student* student_2 = (const Student*)b;
    return strcmp(student_1->surname, student_2->surname);
}

int compare_name(const void* a, const void* b)
{
    const Student* student_1 = (const Student*)a;
    const Student* student_2 = (const Student*)b;
    return strcmp(student_1->name, student_2->name);
}

int compare_group(const void* a, const void* b)
{
    const Student* student_1 = (const Student*)a;
    const Student* student_2 = (const Student*)b;
    return strcmp(student_1->group, student_2->group);
}

int compare_score(const void* a, const void* b)
{
    const Student* student_1 = (const Student*)a;
    const Student* student_2 = (const Student*)b;
    if (fabs(student_1->average_score - student_2->average_score) < EPS)
    {
        return 0;
    }
    return (int)(student_1->average_score - student_2->average_score);
}

