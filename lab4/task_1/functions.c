#include "header.h"

int calculate_hash(const char* key, int size)
{
    unsigned long hash = 0;
    while(*key)
    {
        int digit;
        if (isdigit(*key))
        {
            digit = *key -'0';
        }
        else if (isupper(*key))
        {
            digit = *key - 'A' + 10;
        }
        else if (islower(*key))
        {
            digit = *key - 'a' + 36;
        }
        else if (*key == '\r' || *key == '\n')
        {
            continue;
        }
        else
        {
            return -1;
        }
        hash = hash * 62 + digit;
        key++;
    }
    return (int)(hash % size);
}

Hash_table* create_table(int size)
{
    Hash_table *table = (Hash_table*) malloc(sizeof(Hash_table));
    table->table = (Macro**) calloc(size, sizeof(Macro*));
    if (table->table == NULL)
    {
        free_table(table);
        return NULL;
    }
    table->size = size;
    return table;
}

enum status insert_item(Hash_table* table, const char* key, const char* value)
{
    int hash = calculate_hash(key, table->size);
    if (hash < 0 || hash >=128)
    {
        free_table(table);
        return INPUT_ERROR;
    }
    Macro* new_item = (Macro*) malloc(sizeof(Macro));
    if (new_item == NULL)
    {
        free_table(table);
        return MEMORY_ERROR;
    }
    new_item->key = strdup(key);
    if(new_item->key == NULL)
    {
        free(new_item->key);
        free(new_item->value);
        free(new_item);
        return MEMORY_ERROR;
    }
    new_item->value = strdup(value);
    if (new_item->value == NULL)
    {
        free(new_item->key);
        free(new_item);
        free_table(table);
        return MEMORY_ERROR;
    }
    new_item->hash = hash;
    new_item->next = table->table[hash];
    table->table[hash] = new_item;
    return SUCCESS;
}

char* search_item(Hash_table* table, const char* key)
{
    int hash = calculate_hash(key, table->size);
    Macro * current = table->table[hash];
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void free_table(Hash_table * table)
{
    if (table ==NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; ++i)
    {
        Macro *current = table->table[i];
        while (current)
        {
            Macro* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->table);
    free(table);
}

void print_hash_table(Hash_table* table)
{
    printf("<==============================================================================>\n");
    for (int i = 0; i < table->size; ++i)
    {
        if (table->table[i])
        {
            printf("Cell: %d\n", i);
            Macro *current = table->table[i];
            while (current)
            {
                printf( "Key: '%s', Value: '%s'\n", current->key, current->value);
                current = current->next;
            }
        }
    }
    printf("<==============================================================================>\n");
}

enum status read_file(FILE* file, Hash_table* table)
{
    int capacity = 10, count = 0;
    char* line = (char*)malloc(sizeof(char) * capacity);
    if (line ==NULL)
    {
        fclose(file);
        free_table(table);
        return MEMORY_ERROR;
    }
    char c;
    while((c = fgetc(file)) != EOF)
    {
        if (count >= capacity)
        {
            capacity *= 2;
            char* for_realloc = (char*) realloc(line, sizeof(char) * capacity);
            if (for_realloc == NULL)
            {
                fclose(file);
                free(line);
                free_table(table);
                return MEMORY_ERROR;
            }
            line = for_realloc;
        }

        if (c == '\r' || c == '\n')
        {
            line[count] = '\0';
            if (strncmp(line, "#define", 7) == 0)
            {
                char* token = strtok(line, " ");
                token = strtok(NULL, " ");
                char* name = token;
                token = strtok(NULL, "\n");
                char* value = token;

                if (name && value)
                {
                    enum status error;
                    if ((error = insert_item(table, name, value)) != SUCCESS)
                    {
                        return error;
                    }
                }
            }
            count = 0;
        }
        else
        {
            line[count++] = c;
        }
    }
    if (count > 0) {
        line[count] = '\0';
        if (strncmp(line, "#define", 7) == 0) {
            char* token = strtok(line, " ");
            token = strtok(NULL, " ");
            char* name = token;
            token = strtok(NULL, "\n");
            char* value = token;

            if (name && value) {
                enum status error;
                if ((error = insert_item(table, name, value)) != SUCCESS)
                {
                    return error;
                }
            }
        }
    }
    if (check_and_rebuild_table(table) == MEMORY_ERROR)
    {
        free(line);
        fclose(file);
        free_table(table);
        return MEMORY_ERROR;
    }

    free(line);
    fclose(file);
    return SUCCESS;
}


enum status write_to_file(Hash_table* table, FILE* input, FILE* output)
{
    int capacity = 256;
    char* line = (char *)malloc(capacity * sizeof(char));
    if(line == NULL)
    {
        free_table(table);
        fclose(input);
        fclose(output);
        return MEMORY_ERROR;
    }
    while(fgets(line, capacity, input))
    {
        while (strchr(line, '\n') == NULL && !feof(input))
        {
            capacity *= 2;
            char* for_realloc = (char*) realloc(line, sizeof(char) * capacity);
            if (for_realloc == NULL)
            {
                free(line);
                free_table(table);
                fclose(input);
                fclose(output);
                return MEMORY_ERROR;
            }
            line = for_realloc;
            fgets(line + strlen(line), capacity, input);
        }

        int capacity_word = 10, word_len = 0;
        char* word = (char*) malloc(capacity * sizeof(char));
        char* separators = " .!?,-\t\r\n";
        if (strncmp(line, "#define", 7) == 0)
        {
            continue;
        }
        for (int i = 0; i <= strlen(line); ++i)
        {
            char c = line[i];
            if (( strchr(separators, c))  || c == '\0')
            {
                if (word_len > 0)
                {
                    word[word_len] = '\0';
                    char* replacement = search_item(table, word);
                    if (replacement)
                    {
                        fprintf(output, "%s", replacement);
                    }
                    else
                    {
                        fprintf(output, "%s", word);
                    }
                    word_len = 0;
                }
                if (c != '\0')
                {
                    fprintf(output, "%c", c);
                }
            }
            else
            {
                if (word_len >= capacity - 1)
                {
                    capacity_word *= 2;
                    char* for_realloc = (char*) realloc(word, capacity_word * sizeof(char));
                    if (for_realloc == NULL)
                    {
                        free(word);
                        free(line);
                        free_table(table);
                        fclose(input);
                        fclose(output);
                        return MEMORY_ERROR;
                    }
                    word = for_realloc;
                }
                word[word_len++] = c;
            }
        }
        free(word);
    }
    fclose(input);
    fclose(output);
    free(line);
    return SUCCESS;
}

enum status rebuilding_table(Hash_table* table)
{
    int new_size = table->size * 2;
    Hash_table* new_table = create_table(new_size);
    if (new_table == NULL)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < table->size; ++i)
    {
        Macro* current = table->table[i];
        while(current)
        {
            Macro* next_item = current->next;
            int new_hash = calculate_hash(current->key, new_size);

            current->next = new_table->table[new_hash];
            new_table->table[new_hash] = current;
            current = next_item;
        }
    }
    free(table->table);

    table->table = new_table->table;
    table->size = new_size;
    free_table(new_table);
    return SUCCESS;
}

enum status check_and_rebuild_table(Hash_table* table)
{
    int min = INT_MAX;
    int max = 0;

    for (int i= 0; i<table->size; ++i)
    {
        int length = 0;
        Macro* current = table->table[i];
        while(current)
        {
            length++;
            current = current->next;
        }
        if (length < min)
        {
            min = length;
        }
        if (length > max)
        {
            max = length;
        }
    }

    if (max >= 2*min && min > 0)
    {
        return rebuilding_table(table);
    }
    return SUCCESS;
}