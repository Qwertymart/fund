#include "header.h"

void print_tree(FILE *input, FILE *output)
{
    char *buffer = (char *) malloc(10 * sizeof(char));
    int buf_index = 0, capacity = 10;
    int count = 0;
    char c;

    while ((c = fgetc(input)) != EOF && c != '\n')
    {
        if (c == '(')
        {
            count++;
        }
        else if (c == ')')
        {
            count--;
        }
        else if (c == ' ' || c == ',' || c == '\r')
        {
            continue;
        }
        else
        {
            buf_index = 0;
            while (c != '(' && c != ')' && c != ' ' && c != ',' && c != '\n' && c != EOF && c != '\r')
            {
                if (buf_index >= capacity)
                {
                    capacity *= 2;
                    char *for_realloc = (char *) realloc(buffer, capacity);
                    if (for_realloc == NULL)
                    {
                        free(buffer);
                        printf("Memory error\n");
                        return;
                    }
                    buffer = for_realloc;
                }

                buffer[buf_index++] = c;
                c = fgetc(input);
            }
            buffer[buf_index] = '\0';

            for (int i = 0; i < count * 3; ++i)
            {
                fprintf(output, " ");
            }
            fprintf(output, "|—%s\n", buffer);

            if (c == '(' || c == ')'  || c == ',' || c == '\n')
            ungetc(c, input);
        }
    }
    free(buffer);
}