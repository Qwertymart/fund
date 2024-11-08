#include "header.h"

Node* create_node(const char* word)
{
    Node* new = (Node *) malloc(sizeof(Node));

    if (new == NULL)
    {
        return NULL;
    }
    new->word = (char*) malloc((strlen(word) + 1) *sizeof(char));
    if (new->word == NULL)
    {
        free(new);
        return NULL;
    }
    strcpy(new->word, word);
    new->count = 1;
    new->left = NULL; new->right = NULL;
    return new;
}

Node* insert_node(Node* root, char* word)
{
    if (root == NULL)
    {
        return create_node(word);
    }
    int cmp = strcmp(word, root->word);
    if (cmp == 0)
    {
        root->count++;
    }
    else if (cmp > 0)
    {
        root->right = insert_node(root->right, word);
    }
    else
    {
        root->left = insert_node(root->left, word);
    }
    return root;
}
Node* search_node(Node* root, char* word)
{
    if (root == NULL)
    {
        return NULL;
    }
    int cmp = strcmp(word, root->word);
    if (cmp == 0)
    {
        return root;
    }
    else if(cmp < 0)
    {
        return search_node(root->left, word);
    }
    else
    {
        return search_node(root->right, word);
    }
}

enum status read_file(FILE* file, Node** root, const char* sep)
{
    int capacity_buf = 20;
    char* buf = (char*) malloc(capacity_buf * sizeof(char));
    if (buf == NULL)
    {
        return MEMORY_ERROR;
    }
    buf[0] = '\0';
    char c;
    int i = 0;
    while((c = fgetc(file)) != EOF)
    {
        if (strchr(sep, c) != NULL) // isspace(c)
        {
            if (i > 0)
            {
                    buf[i] = '\0';
                    *root = insert_node(*root, buf);
                    i = 0;
            }
        }
        else
        {
            if (i >= capacity_buf - 1)
            {
                capacity_buf *= 2;
                char* for_realloc = (char *) realloc(buf, capacity_buf);
                if (for_realloc == NULL)
                {
                    free(buf);
                    return MEMORY_ERROR;
                }
                buf = for_realloc;
            }
            buf[i++] = tolower(c);
        }
    }
    if (i > 0)
    {
        buf[i] = '\0';
        *root = insert_node(*root, buf);
    }
    free(buf);
    return SUCCESS;
}

Node* free_tree(Node* root)
{
    if (root)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root->word);
        free(root);
    }
    return NULL;
}

int find_word_frequency(Node* root, char* word)
{
    Node *node = search_node(root, word);
    if (node)
    {
        return node->count;
    }
    return 0;
}

int count_nodes(Node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int compare_freqeuncy(const void* a, const void* b)
{
    Word_frequency* word_1 = (Word_frequency *) a;
    Word_frequency* word_2 = (Word_frequency *) b;
    return word_2->count - word_1->count;
}

void fill_array_from_tree(Node* root, Word_frequency ** array, int* index)
{
    if (root == NULL)
    {
        return;
    }
    fill_array_from_tree(root->left, array, index);
    (*array)[*index].word = root->word;
    (*array)[*index].count = root->count;
    (*index)++;
    fill_array_from_tree(root->right, array, index);
}
void print_top_n(Node* root, int n)
{
    int total_words = count_nodes(root);
    if (n > total_words)
    {
        printf("The total number of words is less\n");
        return;
    }
    Word_frequency* array = (Word_frequency *)malloc(sizeof(Word_frequency) * total_words);
    if (array == NULL)
    {
        printf("Memory error\n");
        return;
    }
    int index = 0;
    fill_array_from_tree(root, &array, &index);
    qsort(array, total_words, sizeof(Word_frequency), compare_freqeuncy);

    for (int i = 0; i < n; ++i)
    {
        printf("%s: %d\n", array[i].word, array[i].count);
    }
    free(array);
}

void find_min_max_words(Node* root, Node** min_node, Node** max_node)
{
    if (root == NULL)
    {
        return;
    }

    if (*min_node == NULL || strlen(root->word) < strlen((*min_node)->word))
    {
        *min_node = root;
    }
    if (*max_node == NULL || strlen(root->word) > strlen((*max_node)->word))
    {
        *max_node = root;
    }

    find_min_max_words(root->left, min_node, max_node);
    find_min_max_words(root->right, min_node, max_node);
}

void print_min_max_words(Node* root)
{
    Node* max = NULL;
    Node* min = NULL;

    find_min_max_words(root, &min, &max);

    if (min != NULL && max != NULL)
    {
        printf("The shortest word: %s\n", min->word);
        printf("The longest word: %s\n", max->word);
    }
    else
    {
        printf("Not found\n");
    }
}

int find_tree_depth(Node* root)
{
    if (root ==NULL)
    {
        return 0;
    }
    int left = find_tree_depth(root->left);
    int right = find_tree_depth(root->right);

    if (left > right)
    {
        return left + 1;
    }
    return right + 1;
}

void save_tree_to_file(Node* root, FILE* file)
{
    if (root == NULL)
    {
        return;
    }
    fprintf(file, "%s\n", root->word);
    save_tree_to_file(root->left, file);
    save_tree_to_file(root->right, file);
}

Node* restore_tree(Node* root, FILE* file)
{
    int capacity_buf = 20;
    char* buf = (char*) malloc(capacity_buf * sizeof(char));
    if (buf == NULL)
    {
        return NULL;
    }
    buf[0] = '\0';
    char c;
    int i = 0;
    while((c = fgetc(file)) != EOF)
    {
        if (c == '\n' && i > 0)
        {
            buf[i] = '\0';
            root = insert_node(root, buf);
            if (root == NULL)
            {
                free(buf);
                return NULL;
            }
            i = 0;
        }

        else
        {
            if (i >= capacity_buf - 1)
            {
                capacity_buf *= 2;
                char* for_realloc = (char *) realloc(buf, capacity_buf);
                if (for_realloc == NULL)
                {
                    free(buf);
                    return NULL;
                }
                buf = for_realloc;
            }
            buf[i++] = tolower(c);
        }
    }
    if (i > 0)
    {
        buf[i] = '\0';
        root = insert_node(root, buf);
    }
    free(buf);
    return root;
}