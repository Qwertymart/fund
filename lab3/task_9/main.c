#include "header.h"

void menu()
{
    printf("\n"
           "1. Number of word occurrences\n"
           "2. First n most common words\n"
           "3. Longest and shortest words\n"
           "4. Depth search\n"
           "5. Saving tree to a file\n"
           "6. Restoring a tree from file\n"
           "7. Exit\n");
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    FILE* input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error opening input file\n");
        return OPEN_ERROR;
    }

    int len_separator = argc - 2;
    char* separator = (char *) malloc(sizeof(char) * (len_separator + 1));
    if (separator == NULL)
    {
        printf("Memory error\n");
        fclose(input);
        return MEMORY_ERROR;
    }
    separator[0] = '\0';

    for (int i = 2; i < argc; ++i)
    {
        if (strlen(argv[i]) != 1)
        {
            printf("Incorrect separator\n");
            fclose(input);
            free(separator);
            return INPUT_ERROR;
        }
        strcat(separator, argv[i]);
    }

    Node* root = NULL;
    if(read_file(input, &root, separator) != SUCCESS)
    {
        printf("Error reading file\n");
        fclose(input);
        free(separator);
        free(root);
        return INPUT_ERROR;
    }
    fclose(input);
    free(separator);


    int flag = 1;
    char choice;
    while(flag)
    {
        menu();
        printf("Your choice: ");
        if (scanf("%c", &choice) != 1)
        {
            printf("Try again\n");
            break;
        }
        while(getchar() != '\n');
        switch (choice)
        {
            case '1':
            {
                if (root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                int capacity = 10, count = 0;
                char* word = (char *) malloc(sizeof(char) * capacity);
                if (word == NULL)
                {
                    printf("Memory error\n");
                    root = free_tree(root);
                    return MEMORY_ERROR;
                }
                printf("Enter word: ");

                char c = getchar();
                while (c != '\n')
                {
                    word[count++] = c;
                    if (count >= capacity)
                    {
                        capacity *= 2;
                        char* for_realloc = (char *) realloc(word, capacity);
                        if( for_realloc == NULL)
                        {
                            printf("Memory error\n");
                            free(word);
                            return MEMORY_ERROR;
                        }
                        word = for_realloc;
                    }
                    c = getchar();
                }
                word[count] = '\0';

                Node* search = search_node(root, word);
                if (search == NULL)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("Number of word <<%s>> found in the text: %d", search->word, search->count);
                }
                free(word);
                break;
            }
            case '2':
            {
                if (root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                printf("Enter <<n>>: ");
                char temp_n[15];
                int n;
                scanf("%15s", temp_n);
                while (getchar() != '\n');
                if (str_to_int(temp_n, &n) != SUCCESS)
                {
                    printf("<n> is too long or write incorrectly\n");
                    break;
                }
                print_top_n(root, n);
                break;
            }
            case '3':
            {
                if (root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                print_min_max_words(root);
                break;
            }
            case '4':
            {
                if(root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                int depth = find_tree_depth(root);
                printf("Depth: %d\n", depth);
                break;
            }
            case '5':
            {
                if (root == NULL)
                {
                    printf("Tree is empty\n");
                    break;
                }
                int capacity = 10, count = 0;
                char* filename = (char *) malloc(sizeof(char) * capacity);
                if (filename == NULL)
                {
                    printf("Memory error\n");
                    root = free_tree(root);
                    return MEMORY_ERROR;
                }
                printf("Enter filename: ");

                char c = getchar();
                while (c != '\n')
                {
                    filename[count++] = c;
                    if (count >= capacity)
                    {
                        capacity *= 2;
                        char* for_realloc = (char *) realloc(filename, capacity);
                        if( for_realloc == NULL)
                        {
                            printf("Memory error\n");
                            free(filename);
                            return MEMORY_ERROR;
                        }
                        filename = for_realloc;
                    }
                    c = getchar();
                }
                filename[count] = '\0';

                char* ind1 = strrchr(argv[1], '/');
                char* ind2 = strrchr(filename, '/');
                int index_1 = 0, index_2 = 0;

                if (ind1 != NULL) index_1 = ind1 - argv[1] + 1;
                if (ind2 != NULL) index_2 = ind2 - filename + 1;

                if (strcmp(argv[1] + index_1, filename + index_2) == 0){
                    printf("Identical file names\n");
                    break;
                }

                FILE *output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("Error opening output file\n");
                    break;
                }
                save_tree_to_file(root, output);
                fclose(output);
                root = free_tree(root);
                break;
            }
            case '6':
            {
                if (root != NULL)
                {
                    printf("Tree is not empty\n");
                    break;
                }
                printf("Enter the filename containing the tree: ");
                int capacity = 10, count = 0;
                char* filename = (char *) malloc(sizeof(char) * capacity);
                if (filename == NULL)
                {
                    printf("Memory error\n");
                    root = free_tree(root);
                    return MEMORY_ERROR;
                }

                char c = getchar();
                while (c != '\n')
                {
                    filename[count++] = c;
                    if (count >= capacity)
                    {
                        capacity *= 2;
                        char* for_realloc = (char *) realloc(filename, capacity);
                        if( for_realloc == NULL)
                        {
                            printf("Memory error\n");
                            free(filename);
                            return MEMORY_ERROR;
                        }
                        filename = for_realloc;
                    }
                    c = getchar();
                }
                filename[count] = '\0';

                char* ind1 = strrchr(argv[1], '/');
                char* ind2 = strrchr(filename, '/');
                int index_1 = 0, index_2 = 0;

                if (ind1 != NULL) index_1 = ind1 - argv[1] + 1;
                if (ind2 != NULL) index_2 = ind2 - filename + 1;

                if (strcmp(argv[1] + index_1, filename + index_2) == 0){
                    printf("Identical file names\n");
                    break;
                }

                FILE* file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("Error opening file\n");
                    break;
                }
                root = restore_tree(root, file);
                break;
            }
            case '7':
            {
                flag = 0;
                break;
            }
            default:
            {
                printf("Invalid choice. Try again\n");
                break;
            }
        }
    }
    root = free_tree(root);
    return 0;
}
