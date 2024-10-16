#include "header.h"

int oversprintf(char * str, char * format, ...)
{
    if (str == NULL || format == NULL) {
        return INPUT_ERROR;
    }
    str[0] = '\0';
    int count = 0;
    int len_format = strlen(format);

    va_list args;
    va_start(args, format);

    for (int i = 0; i < len_format; ++i) {

        if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
            i += 2;
            int value = va_arg(args, int);

            char *res = Ro(value);
            if (res != NULL) {
                count += sprintf(str + count, "%s", res);
            }
            free(res);
        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r') {
            i += 2;

            unsigned int value = va_arg(args, unsigned int);
            char *res = Zr(value);
            if (res != NULL) {
                count += sprintf(str + count, "%s", res);
            }
            free(res);
        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v') {
            i += 2;
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char *res = Cv(num, base);
            if (res != NULL) {
                count += sprintf(str + count, "%s", res);
            }
            free(res);
        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V') {
            i += 2;
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char *res = CV(num, base);
            if (res != NULL) {
                count += sprintf(str + count, "%s", res);
            }
            free(res);
        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 't' && format[i + 2] == 'o') {
            i += 2;
            char *value = va_arg(args, char*);
            int base = va_arg(args, int);

            if (value[0] == '\0') {
                continue;
            }
            int flag = 0;
            int j = 0;
            if (value[0] == '-') {
                j = 1;
            }
            for (j; j < strlen(value); ++j) {
                if (!isalnum(value[j]) || (value[j] >= 'A' && value[j] <= 'Z')) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            int res;
            enum status f = to(value, base, &res);
            if (f != SUCCESS) {
                continue;
            }

            count += sprintf(str + count, "%d", res);

        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'T' && format[i + 2] == 'O') {
            i += 2;

            char *value = va_arg(args, char*);
            int base = va_arg(args, int);
            if (value[0] == '\0') {
                continue;
            }
            int flag = 0;
            int j = 0;
            if (value[0] == '-') {
                j = 1;
            }
            for (j; j < strlen(value); ++j) {
                if (!isalnum(value[j]) || (value[j] >= 'a' && value[j] <= 'z')) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            int res;
            enum status f = to(value, base, &res);
            if (f != SUCCESS) {
                continue;
            }

            count += sprintf(str + count, "%d", res);
        } else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'i') {
            int n = va_arg(args, int);
            char *res = memoru_dump(&n, sizeof(int));
            if (res != NULL) {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'u') {
            unsigned int n = va_arg(args, unsigned int);
            char *res = memoru_dump(&n, sizeof(unsigned int));
            if (res != NULL) {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'd') {
            double n = va_arg(args, double);
            char *res = memoru_dump(&n, sizeof(double));
            if (res != NULL) {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;

        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'f') {
            double n = va_arg(args, double);
            char *res = memoru_dump(&n, sizeof(float));
            if (res != NULL) {
                count += vsprintf(str + count, res, args);
            }
            free(res);
            i += 2;

        } else if (format[i] == '%') {
            char *symbols = "diouxXeEfFgGaAcspn%";
            char *end_type = strpbrk(format + i + 1, symbols);

            if (end_type == NULL) {
                str[count++] = format[i];
                continue;
            }

            int diff = end_type - (format + i) + 1;
            char *mini_format = (char *)malloc(sizeof(char) * (diff + 1));
            if (mini_format == NULL) {
                str[count] = '\0';
                va_end(args);
                return count;
            }
            memcpy(mini_format, format + i  , diff);
            mini_format[diff] = '\0';

            int k = vsnprintf(str + count, sizeof(str) - count, mini_format, args);
            if (k < 0) {
                str[count] = '\0';
                va_end(args);
                free(mini_format);
                return count;
            }

            i += (diff - 1);
            count += k;
            free(mini_format);
        }

        else {
            str[count++] = format[i];
            str[count] = '\0';
        }
    }
    str[count] = '\0';
    va_end(args);
    return count;
}



int overfprintf(FILE * file, char * format, ...)
{
    if (file == NULL || format == NULL)
    {
        return -1;
    }

    int count = 0;
    int len_format = strlen(format);

    va_list args;
    va_start(args, format);

    for (int i = 0; i < len_format; ++i) {

        if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
            i += 2;
            int value = va_arg(args, int);

            char *res = Ro(value);
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r') {
            i += 2;

            unsigned int value = va_arg(args, unsigned int);
            char *res = Zr(value);
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v') {
            i += 2;
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char *res = Cv(num, base);
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V') {
            i += 2;
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char *res = CV(num, base);
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 't' && format[i + 2] == 'o') {
            i += 2;
            char *value = va_arg(args, char*);
            int base = va_arg(args, int);

            if (value[0] == '\0') {
                continue;
            }
            int flag = 0;
            int j = 0;
            if (value[0] == '-') {
                j = 1;
            }
            for (; j < strlen(value); ++j) {
                if (!isalnum(value[j]) || (value[j] >= 'A' && value[j] <= 'Z')) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            int res;
            enum status f = to(value, base, &res);
            if (f != SUCCESS) {
                continue;
            }

            count += fprintf(file, "%d", res);

        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'T' && format[i + 2] == 'O') {
            i += 2;

            char *value = va_arg(args, char*);
            int base = va_arg(args, int);
            if (value[0] == '\0') {
                continue;
            }
            int flag = 0;
            int j = 0;
            if (value[0] == '-') {
                j = 1;
            }
            for (j; j < strlen(value); ++j) {
                if (!isalnum(value[j]) || (value[j] >= 'a' && value[j] <= 'z')) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            int res;
            enum status f = to(value, base, &res);
            if (f != SUCCESS) {
                fclose(file);
                continue;
            }

            count += fprintf(file, "%d", res);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'i') {
            int n = va_arg(args, int);
            char *res = memoru_dump(&n, sizeof(int));
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
            i += 2;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'u') {
            unsigned int n = va_arg(args, unsigned int);
            char *res = memoru_dump(&n, sizeof(unsigned int));
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
            i += 2;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'd') {
            double n = va_arg(args, double);
            char *res = memoru_dump(&n, sizeof(double));
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
            i += 2;

        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'm' && format[i + 2] == 'f') {
            double n = va_arg(args, double);
            char *res = memoru_dump(&n, sizeof(float));
            if (res != NULL) {
                count += fprintf(file, "%s", res);
            }
            free(res);
            i += 2;

        }

        else if (format[i] == '%') {
            char *symbols = "diouxXeEfFgGaAcspn%";
            char *end_type = strpbrk(format + i + 1, symbols);

            if (end_type == NULL) {
                fputc(format[i], file);
                count++;
                continue;
            }

            int diff = end_type - (format + i) + 1;
            char *mini_format = (char *)malloc(sizeof(char) * (diff + 1));
            if (mini_format == NULL) {
                va_end(args);
                return count;
            }
            memcpy(mini_format, format + i  , diff);
            mini_format[diff] = '\0';

            int k = vfprintf(file, mini_format, args);
            if (k < 0) {
                va_end(args);
                free(mini_format);
                return count;
            }

            i += (diff - 1);
            count += k;
            free(mini_format);
        }

        else {
            fputc(format[i], file);
            count++;
        }
    }
    va_end(args);
    return count;
}




