#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "string.h"

typedef long int li;

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

enum status read_file(FILE* f, char* arr, int* len){
    *len = 0;
    char s = fgetc(f);
    while (s == '\n' || s == ' ' || s == '\t' || s == '\r'){
        s = fgetc(f);
    }
    while (s != '\n' && s != ' ' && s != '\t' && s != '\r' && s != EOF){
        arr[*len] = s;
        ++(*len);
        if (*len == 1000){
            return INPUT_ERROR;
        }
        s = fgetc(f);
    }
    arr[*len] = '\0';
    return SUCCESS;
}
void to_base4(int ascii_val, FILE* output) {
    if (ascii_val == 0) {
        fputc('0', output);
        return;
    }

    char base4[20];
    int index = 0;
    while (ascii_val > 0) {
        base4[index++] = (ascii_val % 4) + '0';
        ascii_val /= 4;
    }
    base4[index] = '\0';

    for (int j = index - 1; j >= 0; j--) {
        fputc(base4[j], output);
    }
   // fputc(' ', output);
}

void to_base8(int ascii_val, FILE* output) {
    if (ascii_val == 0) {
        fputc('0', output);
        return;
    }

    char base4[20];
    int index = 0;
    while (ascii_val > 0) {
        base4[index++] = (ascii_val % 8) + '0';
        ascii_val /= 8;
    }
    base4[index] = '\0';

    for (int j = index - 1; j >= 0; j--) {
        fputc(base4[j], output);
    }
    // fputc(' ', output);
}

enum status func_a(FILE* output, char* arr, int len, int count) {
    if (count % 10 == 0 && count != 0) {
        for (int i = 0; i < len; i++) {
            if (arr[i] >= 'A' && arr[i] <= 'Z') {
                arr[i] = arr[i] + 32;
            }
            if (arr[i] >= 'a' && arr[i] <= 'z') {
                to_base4(arr[i], output);
            } else {
                fputc(arr[i], output);
            }
        }
        fputc(' ', output);
    }
    else if(count % 5 == 0){
        for (int i = 0; i < len; i++) {
            if (arr[i] >= 'A' && arr[i] <= 'Z') {
                arr[i] = arr[i] + 32;
            }
            if (arr[i] >= 'a' && arr[i] <= 'z') {
                to_base8(arr[i], output);
            } else {
                fputc(arr[i], output);
            }
        }
        fputc(' ', output);
    }
    else if(count % 2 == 0){
        for (int i = 0; i < len; i++) {
            if (arr[i] >= 'A' && arr[i] <= 'Z') {
                arr[i] = arr[i] + 32;
            }
            fputc(arr[i], output);

        }
        fputc(' ', output);
    }
    else{
        fprintf(output, "%s ", arr);
    }
}


int main(int argc, char* argv[]){
    if (argc < 4){
        printf("Ошибка: некорректный ввод\n");
        return INPUT_ERROR;
    }

    if( !((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0') ) {
        printf("Ошибка: некорректный ввод");
        return INPUT_ERROR;
    }

    switch (argv[1][1]){
        case 'r':{
            if (argc != 5){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            if (strcmp(argv[3], argv[2]) == 0 || strcmp(argv[2], argv[4]) == 0 || strcmp(argv[3], argv[4]) == 0){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            FILE * input1 = fopen(argv[2], "r");
            FILE * input2 = fopen(argv[3], "r");
            FILE * output = fopen(argv[4], "w");
            if(input1 == NULL || input2 == NULL || output == NULL)
            {
                printf("Не удается открыть файл(ы)\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output != NULL) fclose(output);
                return ERROR_OPEN;
            }
            char* arr;
            arr = (char *) malloc(1001*sizeof(char));
            if (arr == NULL){
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output != NULL) fclose(output);
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }

            int len = 0;
            while (!feof(input1) && !feof(input2)) {
                if (read_file(input2, arr, &len) != SUCCESS) {
                    if (input1 != NULL) fclose(input1);
                    if (input2 != NULL) fclose(input2);
                    if (output != NULL) fclose(output);
                    free(arr);
                    return INPUT_ERROR;
                }

                if (len > 0) {
                    fprintf(output, "%s ", arr);
                    len = 0;
                }
                if (read_file(input1, arr, &len) != SUCCESS) {
                    if (input1 != NULL) fclose(input1);
                    if (input2 != NULL) fclose(input2);
                    if (output != NULL) fclose(output);
                    free(arr);
                    return INPUT_ERROR;
                }
                if (len > 0) {
                    fprintf(output, "%s ", arr);
                    len = 0;
                }
            }
            while (!feof(input1)) {
                if (read_file(input1, arr, &len) != SUCCESS) {
                    if (input1 != NULL) fclose(input1);
                    if (input2 != NULL) fclose(input2);
                    if (output != NULL) fclose(output);
                    free(arr);
                    return INPUT_ERROR;
                }

                if (len > 0) {
                    fprintf(output, "%s ", arr);
                    len = 0;
                }
            }

            while (!feof(input2)) {
                if (read_file(input2, arr, &len) != SUCCESS) {
                    if (input1 != NULL) fclose(input1);
                    if (input2 != NULL) fclose(input2);
                    if (output != NULL) fclose(output);
                    free(arr);
                    return INPUT_ERROR;
                }

                if (len > 0) {
                    fprintf(output, "%s ", arr);
                    len = 0;
                }
            }
            printf("Успешно\n");
            if(input1 != NULL) fclose(input1);
            if(input2 != NULL) fclose(input2);
            if(output != NULL) fclose(output);
            free(arr);
            break;
        }
        case 'a':{
            if (argc != 4) {
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            if (strcmp(argv[2], argv[3]) == 0){
                printf("Ошибка: некорректный ввод\n");
                return INPUT_ERROR;
            }
            FILE * input1 = fopen(argv[2], "r");
            FILE * output = fopen(argv[3], "w");
            if(input1 == NULL || output == NULL)
            {
                printf("Не удается открыть файл(ы)\n");
                if(input1 != NULL) fclose(input1);
                if(output != NULL) fclose(output);
                return ERROR_OPEN;
            }
            char* arr;
            arr = (char *) malloc(1001*sizeof(char));
            if (arr == NULL) {
                if (input1 != NULL) fclose(input1);
                if (output != NULL) fclose(output);
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }
            int len = 0, count = 0;
            while(!feof(input1)){
                if (read_file(input1, arr, &len) != SUCCESS) {
                    if (input1 != NULL) fclose(input1);
                    if (output != NULL) fclose(output);
                    free(arr);
                    return INPUT_ERROR;
                }
                count++;
                if (len > 0){
                    func_a(output, arr, len, count);
                }
            }
            fclose(input1);
            fclose(output);
            free(arr);
            printf("Успешно\n");
            break;
        }
    }
}
