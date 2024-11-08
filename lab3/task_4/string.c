#include "header.h"

String create_string(const char* input)
{
    String str;
    str.lenght = (int)strlen(input);
    str.data = (char *) malloc((str.lenght + 1) * sizeof(char));
    if (str.data)
    {
        strcpy(str.data, input);
    }
    return str;
}

void delete_string(String* str)
{
    if (str->data)
    {
        free(str->data);
        str->data = NULL;
    }
    str->lenght = 0;
}

int compare_string(String* str_1, String* str_2)
{
    if (str_1->lenght != str_2->lenght)
    {
        return str_1->lenght - str_2->lenght;
    }
    return strcmp(str_1->data, str_2->data);
}

int equals_string(String* str_1, String* str_2)
{
    return str_1->lenght == str_2->lenght &&
    strcmp(str_1->data, str_2->data) == 0;
}

void copy_string(String* str_1, String* str_2)
{
    if (str_1->data)
    {
        free(str_1->data);
    }
    str_1->lenght = str_2->lenght;
    str_1->data = (char *) malloc((str_2->lenght + 1)*sizeof (char));
    if (str_1->data)
    {
        strcpy(str_1->data, str_2->data);
    }
}

String duplicate_string(String* str)
{
    return create_string(str->data);
}

void concat_string(String* str_1, String* str_2)
{
    char* data = (char *) malloc(
            (str_1->lenght + str_2->lenght + 1)
            * sizeof(char));
    if (data)
    {
        strcpy(data, str_1->data);
        strcat(data, str_2->data);
        free(str_1->data);
        str_1->data = data;
        str_1->lenght = str_1->lenght + str_2->lenght;
    }
}