#include "header.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    enum status result = execute_file(argv[1]);
    switch (result)
    {
        case SUCCESS:
            printf("Execution completed successfully\n");
            break;
        case OPEN_ERROR:
            printf("File open error\n");
            break;
        case MEMORY_ERROR:
            printf("Memory allocation error\n");
            break;
        case INPUT_ERROR:
            printf("Invalid input in file\n");
            break;
        case OVERFLOW_:
            printf("Integer overflow occurred\n");
            break;
        case DIVISION_BY_ZERO:
            printf("Division by zero error\n");
            break;
        case UNINITIALIZED_VARIABLE:
            printf("Attempted to use uninitialized variable\n");
            break;
        default:
            printf("Unknown error occurred\n");
            break;
    }

    return result;
}
