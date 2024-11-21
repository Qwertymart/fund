#include "header.h"

void free_memoryCell(MemoryCell* memoryCell, int count_memoryCell)
{
    for (int i = 0; i < count_memoryCell; ++i)
    {
        free(memoryCell[i].name);
    }
    free(memoryCell);
}

enum status execute_file(char* input_file_name)
{
    FILE* file = fopen(input_file_name, "r");
    if (file == NULL)
    {
        return OPEN_ERROR;
    }
    int capacity_line = 20, count_memoryCell = 0;
    char* line = (char *) malloc(sizeof(char)* capacity_line);
    if(line == NULL)
    {
        fclose(file);
        return MEMORY_ERROR;
    }
    int capacity_memoryCell = 10;
    MemoryCell* memoryCell = (MemoryCell *) malloc(sizeof(MemoryCell) * capacity_memoryCell);
    if (memoryCell == NULL)
    {
        free(line);
        fclose(file);
        return MEMORY_ERROR;
    }
    while (fgets(line, capacity_line, file))
    {
        while (strchr(line, '\n') == NULL && !feof(file))
        {
            capacity_line *= 2;
            char *line_realloc = (char*) realloc(line, sizeof(char) * capacity_line);
            if (line_realloc == NULL)
            {
                free(line);
                free_memoryCell(memoryCell, count_memoryCell);
                fclose(file);
                return MEMORY_ERROR;
            }
            line = line_realloc;
            fgets(line + strlen(line), capacity_line - strlen(line), file);
        }

        if (strchr(line, ';') == NULL)
        {
            free_memoryCell(memoryCell, count_memoryCell);
            free(line);
            fclose(file);
            return INPUT_ERROR;
        }
        if (strncmp(line, "print", 5) == 0)
        {
            if (line[5] == ';')
            {
                print_all_variables(memoryCell, count_memoryCell);
            }
            else
            {
                char* temp = strchr(line, ';');
                if (temp == NULL)
                {
                    free_memoryCell(memoryCell, count_memoryCell);
                    free(line);
                    fclose(file);
                    return INPUT_ERROR;
                }
                *temp = '\0';

                int capacity_name = 10;
                char* name = (char *) malloc(sizeof(char)*capacity_name);
                if (name == NULL)
                {
                    fclose(file);
                    free_memoryCell(memoryCell,count_memoryCell);
                    free(line);
                    return MEMORY_ERROR;
                }

                name = strdup(line + 6);
                if (name == NULL) {
                    free(line);
                    free(name);
                    free_memoryCell(memoryCell, count_memoryCell);
                    fclose(file);
                    return MEMORY_ERROR;
                }
                MemoryCell* variable = find_memoryCell(memoryCell, count_memoryCell, name);
                if (variable == NULL)
                {
                    free(name);
                    free(line);
                    free_memoryCell(memoryCell, count_memoryCell);
                    fclose(file);
                    return UNINITIALIZED_VARIABLE;
                }
                print_variable(variable);
                free(name);
            }
        }
        else if (strchr(line, '='))
        {
            char* temp = strchr(line, ';');
            if (temp == NULL)
            {
                free(line);
                free_memoryCell(memoryCell, count_memoryCell);
                fclose(file);
                return INPUT_ERROR;
            }
            *temp = '\0';

            int capacity_left = 10, count_left = 0;
            int capacity_right = 10, count_right = 0;
            char *name_left = (char *) malloc(capacity_left * sizeof(char));
            if (name_left == NULL)
            {
                free(line);
                free_memoryCell(memoryCell, count_memoryCell);
                fclose(file);
                return MEMORY_ERROR;
            }
            char *name_right = (char *) malloc(capacity_right* sizeof(char ));
            if (name_right == NULL)
            {
                free(name_left);
                free(line);
                free_memoryCell(memoryCell, count_memoryCell);
                fclose(file);
                return MEMORY_ERROR;
            }
            int i = 0;
            for(;line[i] != '='; ++i)
            {
                if (count_left >= capacity_left - 1)
                {
                    capacity_left *= 2;
                    char* left_realloc = (char *) realloc(name_left, capacity_left* sizeof(char));
                    if (left_realloc == NULL)
                    {
                        free(name_left);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        free(name_right);
                        return MEMORY_ERROR;
                    }
                    name_left = left_realloc;
                }
                name_left[i] = line[i];
                ++count_left;
            }
            name_left[count_left] = '\0';

            if (is_valid_name(name_left) == INPUT_ERROR)
            {
                free(name_left);
                free(line);
                free_memoryCell(memoryCell, count_memoryCell);
                fclose(file);
                free(name_right);
                return INPUT_ERROR;
            }

            ++i;
            for (; line[i] != '\0'; ++i)
            {
                if (count_right >= capacity_right)
                {
                    capacity_right *= 2;
                    char* right_realloc = (char*) realloc(name_right, capacity_right * sizeof(char));
                    if (right_realloc == NULL)
                    {
                        free(name_left);
                        free(name_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return MEMORY_ERROR;
                    }
                    name_right = right_realloc;
                }
                name_right[count_right++] = line[i];
            }
            name_right[count_right] = '\0';

            int value_right;
            char* ptr_first_minus;
            char* ptr_second_minus;
            ptr_first_minus = strchr(name_right, '-');
            ptr_second_minus= strrchr(name_right, '-');
            int flag = 0;
            if (ptr_first_minus == NULL)
            {
                flag = 1;
            }
            else if (ptr_second_minus - ptr_first_minus)
            {
                flag = 1;
            }
            else
            {
                if (*(ptr_first_minus - 1) != '=')
                {
                    flag = 1;
                }
            }
            if (flag && (strchr(name_right, '+') || strchr(name_right, '*')
            || strchr(name_right, '/') || strchr(name_right, '-')
            || strchr(name_right, '%')))
            {
                int capacity_name_right_left = 10, count_name_right_left = 0;
                char *name_right_left = (char *) malloc(sizeof(char) * capacity_name_right_left);
                if (name_right_left == NULL) {
                    free(name_left);
                    free(name_right);
                    free(line);
                    free_memoryCell(memoryCell, count_memoryCell);
                    fclose(file);
                    return MEMORY_ERROR;
                }
                int capacity_name_right_right = 10, count_name_right_right = 0;
                char *name_right_right = (char *) malloc(sizeof(char) * capacity_name_right_right);
                if (name_right_right == NULL) {
                    free(name_left);
                    free(name_right);
                    free(line);
                    free_memoryCell(memoryCell, count_memoryCell);
                    fclose(file);
                    free(name_right_left);
                    return MEMORY_ERROR;
                }
                char operator = '\0';
                int j = 0;
                for (; name_right[j] != '\0'; ++j) {
                    if (name_right[j] == '+' || (name_right[j] == '-' && j!=0) ||
                        name_right[j] == '*' || name_right[j] == '/' ||
                        name_right[j] == '%') {
                        operator = name_right[j];
                        ++j;
                        break;
                    }

                    if (count_name_right_left >= capacity_name_right_left) {
                        capacity_name_right_left *= 2;
                        char *new_left = realloc(name_right_left, capacity_name_right_left * sizeof(char));
                        if (new_left == NULL) {
                            free(name_left);
                            free(name_right);
                            free(name_right_left);
                            free(name_right_right);
                            free(line);
                            free_memoryCell(memoryCell, count_memoryCell);
                            fclose(file);
                            return MEMORY_ERROR;
                        }
                        name_right_left = new_left;
                    }

                    name_right_left[count_name_right_left++] = name_right[j];
                }

                name_right_left[count_name_right_left] = '\0';

                for (; name_right[j] != '\0'; ++j) {
                    if (count_name_right_right >= capacity_name_right_right - 1) {
                        capacity_name_right_right *= 2;
                        char *new_right = realloc(name_right_right, capacity_name_right_right * sizeof(char));
                        if (new_right == NULL) {
                            free(name_left);
                            free(name_right);
                            free(name_right_left);
                            free(name_right_right);
                            free(line);
                            free_memoryCell(memoryCell, count_memoryCell);
                            fclose(file);
                            return MEMORY_ERROR;
                        }
                        name_right_right = new_right;
                    }
                    name_right_right[count_name_right_right++] = name_right[j];
                }
                name_right_right[count_name_right_right] = '\0';

                int value_1, value_2;

                if (is_number(name_right_left)) {
                    enum status f = str_to_int(name_right_left, &value_1, 10);
                    if (f != SUCCESS) {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return f;
                    }
                } else {
                    MemoryCell *temp_1 = find_memoryCell(memoryCell, count_memoryCell, name_right_left);
                    if (temp_1 == NULL) {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return UNINITIALIZED_VARIABLE;
                    }
                    value_1 = temp_1->value;
                }

                if (is_number(name_right_right)) {
                    enum status f = str_to_int(name_right_right, &value_2, 10);
                    if (f != SUCCESS) {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return f;
                    }
                } else {
                    MemoryCell *temp_1 = find_memoryCell(memoryCell, count_memoryCell, name_right_right);
                    if (temp_1 == NULL) {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return UNINITIALIZED_VARIABLE;
                    }
                    value_2 = temp_1->value;
                }

                if (operator == '+')
                {
                    if (value_1 > INT_MAX - value_2)
                    {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return OVERFLOW_;
                    }
                    value_right = value_1 + value_2;
                }
                else if (operator == '-')
                {
                    if (value_1 < INT_MIN + value_2)
                    {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return OVERFLOW_;
                    }
                    value_right = value_1 - value_2;
                }
                else if (operator == '*')
                {
                    if (value_1 > abs(INT_MAX / value_2))
                    {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return OVERFLOW_;
                    }
                    value_right = value_1 * value_2;
                }
                else if (operator == '/')
                {
                    if (value_2 == 0)
                    {
                        free(name_left);
                        free(name_right);
                        free(name_right_left);
                        free(name_right_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return DIVISION_BY_ZERO;
                    }
                    value_right = value_1 / value_2;
                }
                else if (operator == '%')
                {
                    value_right = value_1 % value_2;
                }
                else
                {
                    free(name_left);
                    free(name_right);
                    free(name_right_left);
                    free(name_right_right);
                    free(line);
                    free_memoryCell(memoryCell, count_memoryCell);
                    fclose(file);
                    return INPUT_ERROR;
                }
                free(name_right_left);
                free(name_right_right);
            }
            else
            {
                if (is_number(name_right)) {
                    enum status f = str_to_int(name_right, &value_right, 10);
                    if (f != SUCCESS) {
                        free(name_left);
                        free(name_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return f;
                    }
                } else {
                    MemoryCell *temp_1 = find_memoryCell(memoryCell, count_memoryCell, name_right);
                    if (temp_1 == NULL) {
                        free(name_left);
                        free(name_right);
                        free(line);
                        free_memoryCell(memoryCell, count_memoryCell);
                        fclose(file);
                        return UNINITIALIZED_VARIABLE;
                    }
                    value_right = temp_1->value;
                }
            }

            MemoryCell* temp_memoryCell = find_memoryCell(memoryCell, count_memoryCell, name_left);
            if (temp_memoryCell)
            {
                temp_memoryCell->value = value_right;
                qsort(memoryCell, count_memoryCell, sizeof(MemoryCell), compare_memoryCell);
            }
            else
            {
                if (count_memoryCell >= capacity_memoryCell)
                {
                    capacity_memoryCell *= 2;
                    MemoryCell* for_realloc = (MemoryCell *) malloc(capacity_memoryCell * sizeof(MemoryCell));
                    if (for_realloc == NULL)
                    {
                        fclose(file);
                        free_memoryCell(memoryCell, count_memoryCell);
                        free(line);
                        free(name_left);
                        free(name_right);
                        return MEMORY_ERROR;
                    }
                    memoryCell = for_realloc;
                }
                memoryCell[count_memoryCell].name = name_left;
                memoryCell[count_memoryCell].value = value_right;
                count_memoryCell++;
                qsort(memoryCell, count_memoryCell, sizeof(MemoryCell), compare_memoryCell);
            }
        }
    }
    free_memoryCell(memoryCell, count_memoryCell);
    free(line);
    fclose(file);
    return SUCCESS;
}

void print_variable(MemoryCell* memoryCell)
{
    printf("%s = %d\n", memoryCell->name, memoryCell->value);
}

void print_all_variables(MemoryCell* memoryCell, int count)
{
    for (int i = 0; i < count; ++i)
    {
        printf("%s = %d\n", memoryCell[i].name, memoryCell[i].value);
    }
    printf("\n");
}

int compare_memoryCell(const void* a, const void* b)
{
    MemoryCell* memoryCell_1 = (MemoryCell*)a;
    MemoryCell* memoryCell_2 = (MemoryCell*)b;
    return strcmp(memoryCell_1->name, memoryCell_2->name);
}

MemoryCell* find_memoryCell(MemoryCell* memoryCell, int count, char* name)
{
    MemoryCell key;
    key.name = name;
    qsort(memoryCell, count, sizeof(MemoryCell), compare_memoryCell);
    return (MemoryCell *) bsearch(&key, memoryCell, count, sizeof(MemoryCell), compare_memoryCell);
}

int is_number(const char* str)
{

    if (str == NULL || *str == '\0')
    {
        return 0;
    }
    const char* ptr = str;
    if (*ptr == '+' || *ptr == '-')
    {
        ++ptr;
    }
    if (*ptr == '\0') {
        return 0;
    }
    while (*ptr)
    {
        if (!isdigit(*ptr) )
        {
            return 0;
        }
        ++ptr;
    }
    return 1;
}

int is_valid_digit(char ch, int base) {
    if (isdigit(ch)) {
        return (ch - '0') < base;
    } else if (isalpha(ch)) {
        ch = tolower(ch);
        return (ch - 'a' + 10) < base;
    }
    return 0;
}

int is_valid_int(const char* str, int base) {
    if (*str == '-' || *str == '+') {
        str++;
    }

    for (const char* p = str; *p; p++) {
        if (!is_valid_digit(*p, base)) {
            return 0;
        }
    }
    return 1;
}


enum status str_to_int(const char *str, int * result, int base)
{
    if (!(is_valid_int(str, base))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return OVERFLOW_;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, base);

    if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

enum status is_valid_name(const char* name)
{
    for (int i = 0; i < strlen(name); ++i)
    {
        char temp = toupper(name[i]);
        if (!(temp >= 'A' && temp <= 'Z'))
        {
            return INPUT_ERROR;
        }
    }
    return SUCCESS;
}