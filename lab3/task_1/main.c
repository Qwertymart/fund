#include "header.h"

int main()
{
    int capacity = 10;
    char * res = (char*) malloc(sizeof(char) * capacity);
    if (res == NULL)
    {
        printf("Memory error\n");
        return MEMORY_ERROR;
    }
    enum status f = convert_to_base (111, 2, &res, &capacity);

    if (f == MEMORY_ERROR)
    {
        printf("Memory error\n");
        free(res);
        return MEMORY_ERROR;
    }
    else if (f == INPUT_ERROR)
    {
        printf("Input error\n");
        free(res);
        return INPUT_ERROR;
    }
    free(res);
}

