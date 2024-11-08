#include "header.h"

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return INPUT_ERROR;
    }

    char* ind1 = strrchr(argv[1], '/');
    char* ind2 = strrchr(argv[2], '/');
    int index_1 = 0, index_2 = 0;

    if (ind1 != NULL) index_1 = ind1 - argv[1] + 1;
    if (ind2 != NULL) index_2 = ind2 - argv[2] + 1;

    if (strcmp(argv[1] + index_1, argv[2] + index_2) == 0){
        printf("Identical file names\n");
        return INPUT_ERROR;
    }

    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error opening input files\n");
        return INPUT_ERROR;
    }
    FILE * output = fopen(argv[2], "w");
    if(output == NULL)
    {
        printf("Error opening output files\n");
        return INPUT_ERROR;
    }
    int count = 1;
    while (!feof(input))
    {
        fprintf(output, "Tree %d\n", count);
        print_tree(input, output);
        fprintf(output, "\n");
        count++;
    }

    printf("Success\n");


    fclose(input);
    fclose(output);
    return SUCCESS;
}
