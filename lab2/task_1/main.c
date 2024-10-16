#include "header.h"

int main(int argc, char* argv[]){
    if( argc < 3){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    char flag = argv[1][1];
    if (argv[1][0] != '-' && argv[1][0] != '/') {
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }

    switch(flag) {

        case 'f':{
            if (argc != 3){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            char * str = argv[2];
            int len = str_len(str);
            printf("Длина строки: %d\n", len);
            break;
        }
        case 'r':{
            if (argc != 3){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            char * str = argv[2];
            char * result;
            enum status f = reverse_str(str, &result);
            if (f == INPUT_ERROR){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            if (f == MEMORY_ERROR){
                printf("Ошибка выделения памяти");
                return MEMORY_ERROR;
            }
            printf("Перевернутая строка: %s\n", result);
            free(result);
            break;
        }
        case 'u':{
            if (argc != 3){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            char * str = argv[2];
            char * result;
            enum status f = odd_upper(str, &result);
            if (f == INPUT_ERROR){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            if (f == MEMORY_ERROR){
                printf("Ошибка выделения памяти");
                return MEMORY_ERROR;
            }

            printf("%s\n", result);
            free(result);
            break;
        }
        case 'n':{
            if (argc != 3){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            char * str = argv[2];
            char * result;
            enum status f = string_in_order(str, &result);
            if (f == INPUT_ERROR){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            if (f == MEMORY_ERROR){
                printf("Ошибка выделения памяти");
                return MEMORY_ERROR;
            }

            printf("%s\n", result);
            free(result);
            break;
        }
        case 'c':{
            int count = argc - 3;
            if (count == 0){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            unsigned int seed;
            if (str_to_int(argv[2], &seed) != SUCCESS){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            char *result;
            enum status f = concatenation((argv + 3), count, &result, seed);
            if (f == INPUT_ERROR){
                printf("Ошибка: введено некорректно.\n");
                return INPUT_ERROR;
            }
            if (f == MEMORY_ERROR){
                printf("Ошибка выделения памяти");
                return MEMORY_ERROR;
            }
            printf("%s\n", result);
            free(result);
            break;
        }
        default:
            printf("Ошибка: введено некорректно.\n");
            return INPUT_ERROR;
    }
    return SUCCESS;
}
