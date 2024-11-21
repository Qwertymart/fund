#include "header.h"

enum status execute_file_trace(char* input_file_name, Variable * variables, char* trace_name)
{
    FILE* trace = fopen(trace_name, "w");
    if (trace == NULL)
    {
        return OPEN_ERROR;
    }
    int capacity = 50;
    char* line = (char *) malloc(capacity * sizeof(char));
    if (line == NULL)
    {
        fclose(trace);
        return MEMORY_ERROR;
    }
    char* temp_file_name = "temp.txt";
    FILE* temp = fopen(temp_file_name, "w");
    if (temp == NULL)
    {
        free(line);
        fclose(trace);
        return OPEN_ERROR;
    }
    FILE* input = fopen(input_file_name, "r");
    if (input == NULL)
    {
        free(line);
        fclose(temp);
        fclose(trace);
        return OPEN_ERROR;
    }
    if (remove_comments(input, temp) == INPUT_ERROR)
    {
        free(line);
        fclose(input);
        fclose(temp);
        fclose(trace);
        return INPUT_ERROR;
    }
    FILE* file = fopen(temp_file_name, "r");
    if (file == NULL)
    {
        free(line);
        fclose(trace);
        return OPEN_ERROR;
    }

    while (fgets(line, capacity, file) != NULL)
    {
        while (strchr(line, '\n') == NULL && !feof(file))
        {
            capacity *= 2;
            char* line_realloc = (char *) malloc(capacity * sizeof(char));
            if (line_realloc == NULL)
            {
                fclose(file);
                free(line);
                fclose(trace);
                return MEMORY_ERROR;
            }
            line = line_realloc;
            fgets(line + strlen(line), capacity - strlen(line), file);
        }

        char *start = line;
        char* semicolon_position;
        while((semicolon_position = strchr(start, ';')))
        {
            *semicolon_position = '\0';

            enum status res = process_instruction_trace(start, variables, trace);

            if (res != SUCCESS)
            {
                free(line);
                fclose(file);
                fclose(trace);
                return res;
            }
            start = semicolon_position + 1;
        }
    }
    free(line);
    fclose(file);
    fclose(trace);
    return SUCCESS;
}


enum status process_instruction_trace(char* instruction, Variable * variables, FILE* trace)
{
    while (*instruction == ' ' || *instruction == '\t')
    {
        ++instruction;
    }
    if (strncmp(instruction, "read(", 5) == 0)
    {
        char variable;
        char temp_base[3] = {0};
        int index = 5;

        while (instruction[index] == ' ')
        {
            index++;
        }

        if ((instruction[index] >= 'A' && instruction[index] <= 'Z') || (instruction[index] >= 'a' && instruction[index] <= 'z'))
        {
            variable = toupper(instruction[index]);
            index++;
        }
        else
        {
            return INPUT_ERROR;
        }

        while (instruction[index] == ' ' || instruction[index] == ',')
        {
            index++;
        }

        int base_index = 0;
        while (instruction[index] != ')' && instruction[index] != '\0')
        {
            if (base_index < 3)
            {
                temp_base[base_index++] = instruction[index];
                index++;
            }
            else
            {
                return INPUT_ERROR;
            }
        }
        temp_base[base_index] = '\0';
        if (instruction[index] != ')')
        {
            return INPUT_ERROR;
        }
        int base;
        enum status err = str_to_int(temp_base, &base, 10);
        if (err != SUCCESS)
        {
            return err;
        }

        if (base < 2 || base > 36)
        {
            return INVALID_BASE;
        }

        variable = toupper(variable);
        return read_variable_trace(variable, &base, variables, trace);
    }
    else if (strncmp(instruction, "write(", 6) == 0)
    {
        char variable;
        char temp_base[3] = {0};
        int index = 6;

        while (instruction[index] == ' ')
        {
            index++;
        }

        if ((instruction[index] >= 'A' && instruction[index] <= 'Z') || (instruction[index] >= 'a' && instruction[index] <= 'z'))
        {
            variable = toupper(instruction[index]);
            index++;
        }
        else
        {
            return INPUT_ERROR;
        }

        while (instruction[index] == ' ' || instruction[index] == ',')
        {
            index++;
        }

        int base_index = 0;
        while (instruction[index] != ')' && instruction[index] != '\0')
        {
            if (base_index < sizeof(temp_base) - 1)
            {
                temp_base[base_index++] = instruction[index];
                index++;
            }
            else
            {
                return INPUT_ERROR;
            }
        }
        temp_base[base_index] = '\0';

        if (instruction[index] != ')')
        {
            return INPUT_ERROR;
        }

        int base;
        enum status err = str_to_int(temp_base, &base, 10);
        if (err != SUCCESS)
        {
            return err;
        }

        if (base < 2 || base > 36)
        {
            return INVALID_BASE;
        }
        variable = toupper(variable);
        return write_variable_trace(variable, &base, variables, trace);
    }

    else if (strchr(instruction, ':') && strchr(instruction, '='))
    {
        return assigment_variable_trace(instruction, variables, trace);
    }
    else
    {
        return INPUT_ERROR;
    }
}


enum status read_variable_trace(char variable, const int* base, Variable * variables, FILE* trace)
{
    printf("Enter the value for variable %c with base %d: ", variable, *base);
    variable = toupper(variable);
    char temp_value[15];
    int value;

    if (scanf("%15s", temp_value) == 1)
    {
        if (strlen(temp_value) == 15)
        {
            return INPUT_ERROR;
        }
        enum status err;
        if ((err = str_to_int(temp_value, &value, *base)) != SUCCESS)
        {
            return err;
        }
    }
    else {
        return INPUT_ERROR;
    }


    int index;
    if (variable >= 'A' && variable <= 'Z')
    {
        index = variable - 'A';
    }
    else return INPUT_ERROR;
    fprintf(trace, "Before read:\n");
    if (variables[index].init)
    {
        fprintf(trace, "%c = %d\n", variable, variables[index].value);
    }
    else
    {
        fprintf(trace, "%c not initialized\n", variable);
    }
    fprintf(trace, "After read:\n");
    variables[index].value = value;
    variables[index].init = 1;
    fprintf(trace, "%c = %d\n\n", variable, variables[index].value);
    return SUCCESS;
}

enum status write_variable_trace(char variable, const int* base, Variable* variables, FILE* trace)
{
    int index = variable -'A';
    if (index < 0 || index > 26 || variables[index].init == 0)
    {
        return UNINITIALIZED_VARIABLE;
    }

    int value = variables[index].value;
    char output[12];
    int len = snprintf(output, sizeof(output), "%d", value);

    if (len < 0 || len >= sizeof(output)) {
        return OVERFLOW;
    }
    fprintf(trace, "write(%c, %d): %s\n", variable, *base, output);
    return SUCCESS;
}

enum status assigment_variable_trace(char* instruction, Variable* variables, FILE* trace)
{
    while (*instruction == ' ' || *instruction == '\t')
    {
        ++instruction;
    }

    char var, var_1, var_2;
    char op[3] = {0};
    int ind = 0;

    if ((instruction[ind] >= 'A' && instruction[ind] <= 'Z') || (instruction[ind] >= 'a' && instruction[ind] <= 'z'))
    {
        var = toupper(instruction[ind++]);
    }
    else
    {
        return INPUT_ERROR;
    }

    while (instruction[ind] == ' ' || instruction[ind] == ':')
    {
        ind++;
    }
    if (instruction[ind] != '=')
    {
        return INPUT_ERROR;
    }
    ind++;

    while (instruction[ind] == ' ')
    {
        ind++;
    }

    if (instruction[ind] == '\\')
    {
        ++ind;
        if ((instruction[ind] >= 'A' && instruction[ind] <= 'Z') || (instruction[ind] >= 'a' && instruction[ind] <= 'z'))
        {
            var_1 = toupper(instruction[ind++]);
        } else return INPUT_ERROR;
        int index = var - 'A';
        int index_1 = var_1 - 'A';
        fprintf(trace, "Before :=\n");
        if (variables[index].init)
        {
            fprintf(trace, "%c = %d\n", var, variables[index].value);
        }
        else fprintf(trace, "Not init\n");
        if (!variables[index_1].init)
        {
            return UNINITIALIZED_VARIABLE;
        }
        variables[index].init = 1;
        variables[index].value = ~variables[index_1].value;
        fprintf(trace, "After\n%c = %d\n\n", var, variables[index].value);
        return SUCCESS;
    }

    if ((instruction[ind] >= 'A' && instruction[ind] <= 'Z') || (instruction[ind] >= 'a' && instruction[ind] <= 'z'))
    {
        var_1 = toupper(instruction[ind++]);
    }
    else
    {
        return INPUT_ERROR;
    }

    while (instruction[ind] == ' ')
    {
        ind++;
    }

    int op_index = 0;
    while (instruction[ind] != ' ' && instruction[ind] != '\0' && op_index < 2)
    {
        op[op_index++] = instruction[ind++];
    }
    op[op_index] = '\0';

    while (instruction[ind] == ' ')
    {
        ind++;
    }

    if ((instruction[ind] >= 'A' && instruction[ind] <= 'Z') || (instruction[ind] >= 'a' && instruction[ind] <= 'z'))
    {
        var_2 = toupper(instruction[ind++]);
    }
    else
    {
        return INPUT_ERROR;
    }

    if (instruction[ind] != '\0')
    {
        return INPUT_ERROR;
    }

    int index = var - 'A';
    fprintf(trace, "Before := \n");
    if (variables[index].init)
    {
        fprintf(trace, "%c = %d\n", var, variables[index].value);
    }
    else
    {
        fprintf(trace, "%c not init\n", var);
    }
    int index_1 = var_1 - 'A';
    int index_2 = var_2 - 'A';

    if (index_1 < 0 || index_1 >= 26 || index_2 < 0 || index_2 >= 26)
    {
        return INPUT_ERROR;
    }

    if (!variables[index_1].init || !variables[index_2].init)
    {
        return UNINITIALIZED_VARIABLE;
    }
    switch (op[0])
    {
        case '+':
        {
            if (op[1] == '\0')
            {
                variables[index].value = variables[index_1].value | variables[index_2].value;
                variables[index].init = 1;
            }
            else if (op[1] == '>')
            {
                variables[index].value = variables[index_1].value & (!variables[index_2].value);
                variables[index].init = 1;

            }
            else return INPUT_ERROR;
            break;
        }
        case '&':
        {
            variables[index].value = variables[index_1].value & variables[index_2].value;
            variables[index].init = 1;
            break;
        }
        case '-':
        {
            if (op[1] == '>')
            {
                variables[index].value = (!variables[index_1].value) | variables[index_2].value;
                variables[index].init = 1;
                break;
            }
            else return INPUT_ERROR;
        }
        case '<':
        {
            if (op[1] == '-')
            {
                variables[index].value = variables[index_1].value | (!variables[index_2].value);
                variables[index].init = 1;
            }
            else if (op[1] == '>')
            {
                variables[index].value = variables[index_1].value ^ variables[index_2].value;
                variables[index].init = 1;
            }
            else return INPUT_ERROR;
            break;
        }
        case '~':
        {
            variables[index].value = !(variables[index_1].value ^ variables[index_2].value);
            variables[index].init = 1;
            break;
        }
        case '?':
        {
            variables[index].value = !(variables[index_1].value & variables[index_2].value);
            variables[index].init = 1;
            break;
        }
        case '!':
        {
            variables[index].value = !(variables[index_1].value | variables[index_2].value);
            variables[index].init = 1;
            break;
        }
        default:
        {
            return INPUT_ERROR;
        }
    }
    fprintf(trace, "After\n%c = %d\n\n", var, variables[index].value);
    return SUCCESS;
}
