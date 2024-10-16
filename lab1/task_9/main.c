#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <limits.h>
#include <ctype.h>
#include <time.h>

typedef long int li;

enum status {
    INPUT_ERROR, SUCCESS,
    DIVISION_BY_ZERO, ERROR_OPEN,
    MEMORY_ERROR
};

int is_valid_int(const char* str) {

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '-' && *p != '+') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_int(const char *str, int * result)
{
    if (!(is_valid_int(str))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return INPUT_ERROR;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, 10);

    if (temp < INT_MIN || temp > INT_MAX) {
        return INPUT_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

void fillArray(int *arr, int size, int a, int b) {
    for (int i = 0; i < size; i++) {
        arr[i] = a + rand() % (b - a + 1);
    }
}

void findMinMax(int *arr, int size, int *min, int *max){
    if (size <= 0) return;

    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    *min = arr[minIndex];
    *max = arr[maxIndex];
    int temp = arr[minIndex];
    arr[minIndex] = arr[maxIndex];
    arr[maxIndex] = temp;
}

void fill_c(int* c_arr, int b_arr[], int a_arr[], int size_a, int size_b){
    for (int i =0; i < size_a; ++i){
        int min_difference_index = -1;
        int min_difference = INT_MAX;

        for (int j = 0; j < size_b; ++j){
            if (abs(a_arr[i] - b_arr[j])<min_difference){
                min_difference_index = j;
                min_difference = abs(a_arr[i] - b_arr[j]);
            }
        }
        c_arr[i] = a_arr[i] + b_arr[min_difference_index];
    }

}

void print_arr(int arr[], int size){
    for(int i = 0; i < size; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Использование: %s <размер массива> <a> <b>\n", argv[0]);
        return INPUT_ERROR;
    }
    int size, a, b;
    int f1 = str_to_int(argv[1], &size);
    int f2 = str_to_int(argv[2], &a);
    int f3 = str_to_int(argv[3], &b);

    if (f1 != SUCCESS || f2 != SUCCESS || f3 != SUCCESS){
        printf("Некорректные аргументы.\n");
        return INPUT_ERROR;
    }

    if (size <= 0 || a > b) {
        printf("Некорректные аргументы.\n");
        return INPUT_ERROR;
    }

    int arr[size];
    printf("1)\n");
    srand(time(NULL));
    fillArray(arr, size, a, b);

    printf("Сгенерированный массив:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int min, max;

    findMinMax(arr, size, &min, &max);

    printf("Массив после замены местами минимального и максимального элементов:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\nПоменялись местами значения: %d и %d\n", min, max);
    printf("___________________________________________________________________\n");


    printf("2)\n");
    srand(time(NULL));
    int size_a = 10 ;//+ rand() % (10000 - 10 + 1);
    int size_b = 10 ;//+ rand() % (10000 - 10 + 1);
    int a_arr[size_a];
    int b_arr[size_b];

    fillArray(a_arr, size_a, -1000, 1000);
    fillArray(b_arr, size_b, -1000, 1000);

    printf("Массив А:\n");
    print_arr(a_arr, size_a);
    printf("Массив B:\n");
    print_arr(b_arr, size_b);

    int *c_arr = (int *) malloc(size_a * sizeof(int));
    fill_c(c_arr, b_arr, a_arr, size_a, size_b);
    printf("Массив C:\n");
    print_arr(c_arr, size_a);

    free(c_arr);
    return 0;
}