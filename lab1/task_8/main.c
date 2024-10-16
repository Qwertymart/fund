#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "ctype.h"
#include "string.h"

typedef long int li;

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

void min_notation(char* word, int* min_system, int len_word){
    *min_system = 2;
    for (int i = 0; i < len_word; ++i) {
        int value;
        if (isdigit(word[i])) {
            value = word[i] - '0';
        } else if (isalpha(word[i])) {
            value = word[i] - 'A' + 10;
        } else {
            continue;
        }

        if (value + 1 > *min_system) {
            *min_system = value + 1;
        }
    }
}

void convert(int* result, char* word, int len_word, int min_system){
    int degree = len_word - 1;
    *result = 0;
    for(int i = 0; i < len_word; ++i){
        int value;
        if (isdigit(word[i])) {
            value = word[i] - '0';
        } else if (isalpha(word[i])) {
            value = tolower(word[i]) - 'a' + 10;
        }else {
            continue;
        }
        *result += value * pow(min_system, degree);
        --degree;
    }
}

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    if (strcmp(argv[1], argv[2]) == 0){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }
    FILE* fin = fopen(argv[1], "r");
    if (!fin){
        printf("Не удалось открыть файл\n");
        return ERROR_OPEN;
    }
    FILE * fout = fopen(argv[2], "w");
    if(!fout){
        printf("Не удалось открыть файл\n");
        fclose(fin);
        return ERROR_OPEN;
    }
    char word[100];
    int n = 0, len_word = 0;
    char c;
    int min_system = 2;
    int sign = 0;
    while(!feof(fin)){
        c = fgetc(fin);
        if (c == ' ' || c == '\n' || c == '\t'
        || c == '\r' || c == EOF){
            if (len_word > 0){
                min_notation(word, &min_system, len_word);
                if(min_system > 36 || min_system < 2){
                    printf("Ошибка: некорректный ввод\n");
                    fclose(fin);
                    fclose(fout);
                    return INPUT_ERROR;
                }else{
                    fprintf(fout, "%d : ", min_system);
                    int flag = 0;
                    if (sign == -1) fprintf(fout, "-");
                    for (int i = 0; i < len_word; ++i){
                        if (flag == 1){
                            fprintf(fout, "%c", word[i]);
                        }
                        else if (word[i] != '0'){
                            flag = 1;
                            fprintf(fout, "%c", word[i]);
                        }
                    }

                    int result = 0;
                    convert(&result, word, len_word, min_system);
                    if (result == 0){
                        fprintf(fout, "0");
                    }
                    if (sign == -1) fprintf(fout, " : -%d\n", result);
                    else fprintf(fout, " : %d\n", result);
                    sign = 0;
                }
                n = 0;
                len_word = 0;
            }

        }else if (c == '-'){
            sign = -1;
        }else{
            if (n >= sizeof(word) - 1){
                printf("Ошибка: некорректный ввод\n");
                fclose(fin);
                fclose(fout);
                return INPUT_ERROR;
            }
            word[n] = toupper(c);
            ++n;
            ++len_word;
        }

    }
    printf("Успешно\n");
    fclose(fin);
    fclose(fout);
    return 0;
}