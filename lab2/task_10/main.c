#include "header.h"

int main() {
    double *result;
    enum status err;
    int degree = 1;
    err = polynomial(-1.0, &result, 1, 7.0, 2.0);
    if (err == SUCCESS)
    {
        for (int i = 0; i <= degree; ++i)
        {
            printf("%lf ", result[i]);
        }
        printf("\n");
    }
    else if (err == INPUT_ERROR)
    {
        printf("Input error\n");
    }
    else if (err == MEMORY_ERROR)
    {
        printf("Memory error\n");
    }

    free(result);
    return 0;
}