#include "header.h"

int main(int argc, char* argv[])
{
    Variable variable[26];
    for (int i = 0; i < 26; ++i)
    {
        variable[i].init = 0;
    }

    if (argc == 2)
    {
        enum status res = execute_file(argv[1], variable);
        if (res == MEMORY_ERROR)
        {
            printf("Memory allocation error\n");
            return MEMORY_ERROR;
        }
        else if (res == OPEN_ERROR)
        {
            printf("Error opening file\n");
            return OPEN_ERROR;
        }
        else if (res == INVALID_BASE)
        {
            printf("Invalid base\n");
            return INVALID_BASE;
        }
        else if(res == UNINITIALIZED_VARIABLE)
        {
            printf("Uninitialized variable\n");
            return UNINITIALIZED_VARIABLE;
        }
        else if (res == INPUT_ERROR)
        {
            printf("Input error\n");
            return INPUT_ERROR;
        }
        else
        {
            printf("Success\n");
            return SUCCESS;
        }
    }
    else if (argc == 4)
    {
        if (strcmp(argv[2], "/trace") != 0)
        {
            printf("Input error\n");
            return INPUT_ERROR;
        }
        char* ind1 = strrchr(argv[1], '/');
        char* ind2 = strrchr(argv[3], '/');
        int index_1 = 0, index_2 = 0;

        if (ind1 != NULL) index_1 = ind1 - argv[1] + 1;
        if (ind2 != NULL) index_2 = ind2 - argv[3] + 1;

        if (strcmp(argv[1] + index_1, argv[3] + index_2) == 0){
            printf("Identical file names\n");
            return INPUT_ERROR;
        }

        enum status res = execute_file_trace(argv[1], variable, argv[3]);
        if (res == MEMORY_ERROR)
        {
            printf("Memory allocation error\n");
            return MEMORY_ERROR;
        }
        else if (res == OPEN_ERROR)
        {
            printf("Error opening file\n");
            return OPEN_ERROR;
        }
        else if (res == INVALID_BASE)
        {
            printf("Invalid base\n");
            return INVALID_BASE;
        }
        else if(res == UNINITIALIZED_VARIABLE)
        {
            printf("Uninitialized variable\n");
            return UNINITIALIZED_VARIABLE;
        }
        else if (res == INPUT_ERROR)
        {
            printf("Input error\n");
            return INPUT_ERROR;
        }
        else
        {
            printf("Success\n");
            return SUCCESS;
        }

    }
    return SUCCESS;
}