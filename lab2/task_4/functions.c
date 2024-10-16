#include "header.h"

int cross_product(Point a, Point b, Point c) {
    double cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (cross > 0) return 1;  // левый поворот
    if (cross < 0) return -1; // правый поворот
    return 0;
}


enum status convex(enum conv* result, int num_points, ...) {
    va_list args;
    va_start(args, num_points);
    Point* points = (Point*) malloc(num_points * sizeof(Point));
    if (points == NULL) {
        va_end(args);
        return MEMORY_ERROR;
    }
    for (int i = 0; i < num_points; ++i) {
        points[i] = va_arg(args, Point);
    }
    va_end(args);

    int direction = 0;
    int first_nonzero_cross = 0;

    for (int i = 0; i < num_points; ++i) {
        int cross = cross_product(points[i], points[(i + 1) % num_points], points[(i + 2) % num_points]);

        if (cross != 0) {
            if (first_nonzero_cross == 0) {
                direction = cross;
                first_nonzero_cross = 1;
            } else if (direction != cross) {
                free(points);
                *result = NOT_CONVEX;
                return SUCCESS;
            }
        }
    }

    *result = CONVEX;
    free(points);
    return SUCCESS;
}

enum status polynomial(double *result, double x, int n, ...)
{
    va_list args;
    va_start(args, n);

    double coeff = va_arg(args, double);
    *result = coeff;

    for (int i = 1; i <= n; ++i) {
        coeff = va_arg(args, double);

        if (*result > (DBL_MAX - coeff) / x) {
            va_end(args);
            return OVERFLOW_ERROR;
        }

        *result = *result * x + coeff;
    }

    va_end(args);
    return SUCCESS;
}


int is_valid_int(const char* str) {

    for (const char* p = str; *p; p++) {
        if (!isdigit(*p) && *p != '-' && *p != '+') {
            return 0;
        }
    }
    return 1;
}

enum status str_to_int(const char *str, int * result, int base)
{
    if (!(is_valid_int(str))){
        return INPUT_ERROR;
    }
    size_t len = strlen(str);
    if (len > 11 || (len == 11 && str[0] == '-' && str[1] > '2') || (len == 10 && str[0] != '-')) {
        return OVERFLOW_ERROR;
    }
    char *endptr;
    long long temp;
    temp = strtol(str, &endptr, base);

    if (temp < INT_MIN || temp > INT_MAX) {
        return OVERFLOW_ERROR;
    } else if (*endptr != '\0') {
        return INPUT_ERROR;
    }
    *result = (int)temp;
    return SUCCESS;
}

void int_to_str_base(int num, int base, char* str)
{
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index = 0;
    long long temp = num;

    while (temp > 0) {
        str[index++] = digits[temp % base];
        temp /= base;
    }
    str[index] = '\0';

    for (int i = 0; i < index / 2; ++i) {
        char tmp = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = tmp;
    }
}

enum status is_kaprekar(int num, int base, int *kaprekar)
{
    if (num == 0) {
        *kaprekar = 0;
        return SUCCESS;
    }

    int square = num * num;
    char buff[64];
    int_to_str_base(square, base, buff);

    int len = strlen(buff);
    for (int i = 1; i < len; ++i) {
        char left[32], right[32];
        strncpy(left, buff, i);
        left[i] = '\0';
        strcpy(right, buff + i);

        int left_num, right_num;

        enum status f_l = str_to_int(left, &left_num, base);
        if (f_l != SUCCESS) {
            return f_l;
        }

        enum status f_r = str_to_int(right, &right_num, base);
        if (f_r != SUCCESS) {
            return f_r;
        }

        if (right_num != 0 && left_num + right_num == num) {
            *kaprekar = 1;
            return SUCCESS;
        }
    }
    *kaprekar = 0;
    return SUCCESS;
}

enum status find_kaprekar(int base, int num_args, ...)
{
    va_list args;
    va_start(args, num_args);

    printf("Числа Капрекара в системе счисления с основанием %d:\n", base);

    for (int i = 0; i < num_args; i++) {
        char* str_num = va_arg(args, char*);

        int num = strtol(str_num, NULL, base);
        int kaprekar = 0;
        enum status f = is_kaprekar(num, base, &kaprekar);
        if (f == INPUT_ERROR){
            va_end(args);
            return INPUT_ERROR;
        }
        if (f == OVERFLOW_ERROR){
            return OVERFLOW_ERROR;
        }

        if (kaprekar){
            printf("%s является числом Капрекара\n", str_num);
        } else {
            printf("%s не является числом Капрекара\n", str_num);
        }
    }

    va_end(args);
    return SUCCESS;
}