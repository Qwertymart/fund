#include "header.h"

int main()
{
    char *result;

    enum status f = sum(&result, 10, 2, "123", "456");
    if (f == INPUT_ERROR) {
        printf("Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 1: %s\n", result); // 579
    }
    free(result);


    f = sum(&result, 10, 3, "1", "999", "1");
    if (f == INPUT_ERROR) {
        printf("Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 2: %s\n", result);//1001
    }
    free(result);


    f = sum(&result, 2, 2, "1101", "1011");
    if (f == INPUT_ERROR) {
        printf("Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 3: %s\n", result); // 11000
    }
    free(result);


    f = sum(&result, 10, 2, "9999999999999999999999999", "1");
    if (f == INPUT_ERROR) {
        printf("Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 4: %s\n", result); //100000000000000000000000
    }
    free(result);


    f = sum(&result, 12, 2, "A", "1");
    if (f == INPUT_ERROR) {
        printf("Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 5: %s\n", result); // B
    }
    free(result);


    f = sum(&result, 2, 3, "0", "0", "00010000");
    if (f == INPUT_ERROR) {
        printf("Test 6: Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 6: %s\n", result); // основание
    }



    f = sum(&result, 37, 2, "123", "456"); // основание
    if (f == INPUT_ERROR) {
        printf("Test 7: Input error\n");
    }

    f = sum(&result, 10, 2, "", "123");
    if (f == INPUT_ERROR) {
        printf("Test 8: Input error\n");
    }

    f = sum(&result, 10, 2,
            "9999999999999999999999999999999999999999999999999999999999999",
            "1");
    if (f == INPUT_ERROR) {
        printf("Test 9: Input error\n");
    } else if (f == MEMORY_ERROR) {
        printf("Test 9: Memory error\n");
    } else if (f == SUCCESS) {
        printf("Test 9: %s\n", result); // Ожидаемый вывод: 10000000000000000000000000000000000000000000000000000000000000
    }
    free(result);

    f = sum(&result, 10, 2, "-123", "456");
    if (f == INPUT_ERROR) {
        printf("Test 10: Input error\n");
    }

    return 0;
}
