#include "header.h"

int main(){
    enum conv result;

    //Выпуклый
    Point p1 = (Point){0, 0};
    Point p2 = (Point){1, 0};
    Point p3 = (Point){1, 1};
    Point p4 = (Point){0, 1};


    Point t1 = (Point){0, 0};
    Point t2 = (Point){1, 1};
    Point t3 = (Point){2, 0};
    Point t4 = (Point){3, 1};
    Point t5 = (Point){4, 0};

    enum status f1 = convex(&result, 5, t1, t2, t3, t4, t5);
    printf("Тест 1: ");
    if (f1 == MEMORY_ERROR) {
        printf("Ошибка: не удалось выделить память\n");
    } else if (result == CONVEX) {
        printf("Выпуклый\n");
    } else {
        printf("Не выпуклый\n");
    }

    //Выпуклый
    Point p5 = (Point){0, 0};
    Point p6 = (Point){2, 0};
    Point p7 = (Point){2, 1};
    Point p8 = (Point){1, 2};
    Point p9 = (Point){0, 1};
    f1 = convex(&result, 5, p5, p6, p7, p8, p9);
    printf("Тест 2: ");
    if (f1 == MEMORY_ERROR) {
        printf("Ошибка: не удалось выделить память\n");
    } else if (result == CONVEX) {
        printf("Выпуклый\n");
    } else {
        printf("Не выпуклый\n");
    }

    //Невыпуклый
    Point p10 = (Point){0, 0};
    Point p11 = (Point){2, 0};
    Point p12 = (Point){1, 1};
    Point p13 = (Point){2, 2};
    Point p14 = (Point){0, 1};
    f1 = convex(&result, 5, p10, p11, p12, p13, p14);
    printf("Тест 3: ");
    if (f1 == MEMORY_ERROR) {
        printf("Ошибка: не удалось выделить память\n");
    } else if (result == CONVEX) {
        printf("Выпуклый\n");
    } else {
        printf("Не выпуклый\n");
    }

    //Невыпуклый
    Point p15 = (Point){0, 0};
    Point p16 = (Point){1, 2};
    Point p17 = (Point){2, 0};
    Point p18 = (Point){1, 1};
    f1 = convex(&result, 4, p15, p16, p17, p18);
    printf("Тест 4: ");
    if (f1 == MEMORY_ERROR) {
        printf("Ошибка: не удалось выделить память\n");
    } else if (result == CONVEX) {
        printf("Выпуклый\n");
    } else {
        printf("Не выпуклый\n");
    }

    printf("__________________________________\n");


    double result_polinomial;
    enum status f2 = polynomial(&result_polinomial, 2.0, 2, 2., 1., 3.);
    if (f2 == OVERFLOW_ERROR){
        printf("Ошибка: переполнение\n");
        return f2;
    }
    if (f2 == SUCCESS){
        printf("%lf\n", result_polinomial);
    }
    printf("__________________________________\n");


    enum status f3 = find_kaprekar(10, 5, "A", "297", "4879", "1", "345678903456789021212333");
    if (f3 == OVERFLOW_ERROR){
        printf("Ошибка: переполнение\n");
    }
    if (f3 == INPUT_ERROR){
        printf("Ошибка: введено некорректно\n");
    }
    printf("\n");

    enum status f4 = find_kaprekar(16, 5, "1", "0", "CCC", "4444", "45");
    if (f4 == OVERFLOW_ERROR){
        printf("Ошибка: переполнение\n");
    }
    if (f3 == INPUT_ERROR){
        printf("Ошибка: введено некорректно\n");
    }

    return 0;
}
