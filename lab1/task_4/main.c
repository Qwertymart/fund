#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
typedef long int li;

enum status{
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

enum status func_d(FILE* input, FILE* output){
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ferror(input)) {
            printf("Ошибка: проблема с чтением файла\n");
            return ERROR_OPEN;
        }
        if (ch < '0' || ch > '9') {
            fputc(ch, output);
        }
    }
    return SUCCESS;
}

enum status func_i(FILE* input, FILE* output){
    char ch;
    int count_str = 1, count_letter = 0;
    while ((ch = fgetc(input)) != EOF){
        if (ferror(input)) {
            printf("Ошибка: проблема с чтением файла\n");
            return ERROR_OPEN;
        }

        if(ch == '\n')
        {
            fprintf(output, "%d. %d\n", count_str, count_letter);
            count_str++;
            count_letter = 0;
        }
        else if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
            ++count_letter;
        }
    }
    fprintf(output, "%d. %d\n", count_str, count_letter);
    return SUCCESS;

}

enum status func_s(FILE* input, FILE* output) {
    char ch;
    int count_str = 1, count_letter = 0;
    while ((ch = fgetc(input)) != EOF) {
        if (ferror(input)) {
            printf("Ошибка: проблема с чтением файла\n");
            return ERROR_OPEN;
        }

        if (isalnum(ch) || ch == ' ')
            continue;
        else if(ch == '\n')
        {
            fprintf(output, "%d. %d\n", count_str, count_letter - 1);
            count_str++;
            count_letter = 0;
        }
        else{
            ++count_letter;
        }

    }
    fprintf(output, "%d. %d\n", count_str, count_letter);
    return SUCCESS;
}

enum status func_a(FILE* input, FILE* output){
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ferror(input)) {
            printf("Ошибка: проблема с чтением файла\n");
            return ERROR_OPEN;
        }
        if ((ch >= '0' && ch <= '9')){
            fprintf(output, "%c", ch);
        } else if (ch == '\n' || ch == ' ' || ch == '\t'){
            fprintf(output, " ");
        }
        else if (ch != '\r'){
            fprintf(output, "%X", ch);
        }
    }
    return SUCCESS;
}

int main(int argc, char* argv[]){
    if (argc < 3)
    {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    if( !((argv[1][0] == '-' || argv[1][0] == '/') && (argv[1][2] == '\0' || argv[1][3] == '\0')) ) {
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    FILE *input = fopen(argv[2], "r");
    if (input == NULL)
    {
        printf("Ошибка: не получилось открыть файл %s\n", argv[2]);
        return ERROR_OPEN;
    }
    FILE *output = NULL;
    int size_flag = strlen(argv[1]);

    if(size_flag == 3){
        if (argc != 4){
            printf("Ошибка: некорректный ввод\n");
            fclose(input);
            return INPUT_ERROR;
        }
        if (argv[1][1] == 'n'){
            char* ind1 = strrchr(argv[3], '/');
            char* ind2 = strrchr(argv[2], '/');
            int index_1 = 0, index_2 = 0;

            if (ind1 != NULL) index_1 = ind1 - argv[3] + 1;
            if (ind2 != NULL) index_2 = ind2 - argv[2] + 1;

            if (strcmp(argv[3] + index_1, argv[2] + index_2) == 0){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            output = fopen(argv[3], "w");
            if (output == NULL){
                printf("Ошибка: не получилось открыть файл %s\n", argv[3]);
                fclose(input);
                return ERROR_OPEN;
            }
        }
        else{
            printf("Ошибка: некорректный ввод\n");
            fclose(input);
            return INPUT_ERROR;
        }
    }
    else if (size_flag == 2){
        if (argc != 3){
            printf("Ошибка: некорректный ввод\n");
            fclose(input);
            return INPUT_ERROR;
        }

        char* out_file = (char*) malloc((strlen(argv[2]) + strlen("out_") + 1) * sizeof(char));
        if(out_file == NULL){
            printf("Ошибка: некорректный ввод\n");
            fclose(input);
            return INPUT_ERROR;
        }
        char* end = strrchr(argv[2], '/');
        if(end == NULL){
            strcpy(out_file, "out_");
            strcat(out_file, argv[2]);
            out_file[strlen(argv[2]) + 4] = '\0';
        }
        else{
            size_t s = strlen(argv[2]);
            size_t shift = s - strlen(end);

            memcpy(out_file, argv[2], shift);
            memcpy(out_file + shift, "/out_", 5);
            shift += 5;
            memcpy(out_file + shift, end + 1, strlen(end) - 1);
            out_file[s + 4] = '\0';
        }

        output = fopen(out_file, "w");
        if(output == NULL) {
            printf("Ошибка: не получилось открыть файл %s\n", out_file);
            fclose(input);
            return ERROR_OPEN;
        }
    }
    switch (argv[1][size_flag - 1]){
        case 'd':{
            enum status f = func_d(input, output);
            if(f == SUCCESS){
                printf("Операция выполнилась успешно\n");
            }
            fclose(input);
            fclose(output);
            break;
        }
        case 'i':{
            enum status f = func_i(input, output);
            if(f == SUCCESS){
                printf("Операция выполнилась успешно\n");
            }
            fclose(input);
            fclose(output);
            break;
        }
        case 's':{
            enum status f = func_s(input, output);
            if(f == SUCCESS){
                printf("Операция выполнилась успешно\n");
            }
            fclose(input);
            fclose(output);
            break;
        }
        case 'a':{
            enum status f = func_a(input, output);
            if(f == SUCCESS){
                printf("Операция выполнилась успешно\n");
            }
            fclose(input);
            fclose(output);
            break;
        }
        default:
            printf("Ошибка: такого флага нет в доступных флагах\n");
            return INPUT_ERROR;
    }
    return 0;
}