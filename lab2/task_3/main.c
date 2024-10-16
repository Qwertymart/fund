#include "header.h"

int main(){
    enum status f = file_pocessing("abc", 2, "/mnt/c/Users/u/CLionProjects/fund/lab2/task_3/1.txt", "2.txt");
    if (f == INPUT_ERROR){
        printf("Ошибка: введено некорректно.\n");
        return INPUT_ERROR;
    }
    else if (f == ERROR_OPEN){
        printf("Ошибка: не удается открыть файл\n");
        return ERROR_OPEN;
    }
    else if (f == MEMORY_ERROR){
        printf("Ошибка: не удалось выделить память\n");
        return MEMORY_ERROR;
    }
}
