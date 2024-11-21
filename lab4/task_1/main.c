#include "header.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Input error\n");
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

    Hash_table* table = create_table(SIZE_TABLE);

    if (!table)
    {
        printf("Failed to create table\n");
        return INPUT_ERROR;
    }
    else
    {
        printf("Managed to create the table\n");
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        free_table(table);
        printf("Error opening input file\n");
        return OPEN_ERROR;
    }
    enum status error = read_file(input, table);
    if (error == MEMORY_ERROR)
    {
        printf("Memory error when reading input file\n");
        return MEMORY_ERROR;
    }
    else if (error == INPUT_ERROR)
    {
        printf("Invalid define name\n");
        return INPUT_ERROR;
    }
    else if (error == SUCCESS)
    {
        printf ("File read successfully\n");
    }

    print_hash_table(table);

    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Error opening input file\n");
        free_table(table);
        return OPEN_ERROR;
    }
    FILE* output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Error opening output file\n");
        free_table(table);
        fclose(input);
        return OPEN_ERROR;
    }

    error = write_to_file(table, input, output);
    if (error == MEMORY_ERROR)
    {
        printf("Memory error when write to output file\n");
        return MEMORY_ERROR;
    }
    else if (error == SUCCESS){
        printf("Write to output file successfully\n");
    }
    free_table(table);

    return SUCCESS;
}