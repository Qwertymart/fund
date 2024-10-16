#include "header.h"


int oversscanf(char *str, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    int count = 0;
    int len_format = strlen(format);
    int i = 0;

    while( i < len_format)
    {
        if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
            i += 2;
            char format_end = format[i+3];
            int index_plus = 0;
            int *value = va_arg(args, int*);
            *value = Ro(str, &index_plus, format_end);
            str += index_plus - 1;
            count++;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;
            int *value = va_arg(args, int*);
            *value = Zr(str, format_end, &index_plus);
            str += index_plus - 1;
            ++count;
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;
            int *value = va_arg(args, int*);
            int base = va_arg(args, int);
            enum status f = Cv(str, format_end, base, value, &index_plus);
            if (f == SUCCESS)
            {
                str += index_plus - 1;
                ++count;
            }
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;
            int *value = va_arg(args, int*);
            int base = va_arg(args, int);
            enum status f = Cv(str, format_end, base, value, &index_plus);
            if (f == SUCCESS)
            {
                str += index_plus - 1;
                ++count;
            }
        }

        else if (format[i] == '%') {
            char *symbols = "diouxXeEfFgGaAcspn%";
            char *end_type = strpbrk(format + i + 1, symbols);
            void* value = va_arg(args, void*);

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
            memcpy(mini_format, format + i   , diff);
            printf("%s\n", mini_format);
            mini_format[diff] = '\0';
            int k = sscanf(str, mini_format, value);
            if (k < 0) {
                str[count] = '\0';
                va_end(args);
                free(mini_format);
                return count;
            }
            str += diff;
            i += (diff - 1);
            count += k;
            free(mini_format);
        }

        else {
            ++i;
            ++str;
        }
    }
    va_end(args);
    return count;
}


int overfscanf(FILE* f, char* format, ...)
{
    va_list args;
    va_start(args, format);

    int count = 0;
    int len_format = strlen(format);
    int i = 0;

    while( i < len_format)
    {
        if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'R' && format[i + 2] == 'o') {
            char format_end = format[i+3];
            i += 2;

            char c = fgetc(f);
            char *str = (char *) malloc(12 * sizeof(int));
            if(str == NULL)
            {
                va_end(args);
                return count;
            }
            int j = 0;
            while (c != EOF && c != format_end)
            {
                str[j++] = c;
                c = fgetc(f);
            }
            str[j] = '\0';
            int index_plus = 0;
            int *value = va_arg(args, int*);
            *value = Ro(str, &index_plus, format_end);
            count++;
            free(str);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'Z' && format[i + 2] == 'r')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;

            char c = fgetc(f);
            char *str = (char *) malloc(12 * sizeof(int));
            if(str == NULL)
            {
                va_end(args);
                return count;
            }
            int j = 0;
            while (c != EOF && c != format_end)
            {
                str[j++] = c;
                c = fgetc(f);
            }
            str[j] = '\0';

            int *value = va_arg(args, int*);
            *value = Zr(str, format_end, &index_plus);
            ++count;
            free(str);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'v')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;

            char c = fgetc(f);
            char *str = (char *) malloc(12 * sizeof(int));
            if(str == NULL)
            {
                va_end(args);
                return count;
            }
            int j = 0;
            while (c != EOF && c != format_end)
            {
                str[j++] = c;
                c = fgetc(f);
            }
            str[j] = '\0';

            int *value = va_arg(args, int*);
            int base = va_arg(args, int);
            enum status f = Cv(str, format_end, base, value, &index_plus);
            if (f == SUCCESS)
            {
                ++count;
            }
            free(str);
        }

        else if (format[i] == '%' && i < len_format - 2 && format[i + 1] == 'C' && format[i + 2] == 'V')
        {
            char format_end = format[i+3];
            int index_plus = 0;
            i += 2;

            char c = fgetc(f);
            char *str = (char *) malloc(12 * sizeof(int));
            if(str == NULL)
            {
                va_end(args);
                return count;
            }
            int j = 0;
            while (c != EOF && c != format_end)
            {
                str[j++] = c;
                c = fgetc(f);
            }
            str[j] = '\0';

            int *value = va_arg(args, int*);
            int base = va_arg(args, int);
            enum status f = Cv(str, format_end, base, value, &index_plus);
            if (f == SUCCESS)
            {
                str += index_plus - 1;
                ++count;
            }
            free(str);
        }

        else if (format[i] == '%') {
            int j = 0;
            char format_end = '\0';
            for (; i + j < strlen(format); ++j)
            {
                if (format[i + j] == ' ' ||
                        format[i + j] == '\t' ||
                        format[i + j] == '\n' ||
                        format[i + j] == '\0' ||
                        format[i + j] == '\r')
                {
                    format_end = format[i + j];
                    break;
                }
            }

            char c = fgetc(f);
            char *str = (char *) malloc(120 * sizeof(int));
            if(str == NULL)
            {
                va_end(args);
                return count;
            }
            int str_index = 0;
            while (c != EOF && c != format_end)
            {
                str[str_index++] = c;
                c = fgetc(f);
            }
            str[str_index] = '\0';

            char *symbols = "diouxXeEfFgGaAcspn%";
            char *end_type = strpbrk(format + i + 1, symbols);
            void* value = va_arg(args, void*);

            if (end_type == NULL) {
                str[count++] = format[i];
                va_end(args);
                continue;
            }

            int diff = end_type - (format + i) + 1;
            char *mini_format = (char *)malloc(sizeof(char) * (diff + 1));
            if (mini_format == NULL) {
                va_end(args);
                free(str);
                return count;
            }
            memcpy(mini_format, format + i, diff);
            mini_format[diff] = '\0';
            int k = sscanf(str, mini_format, value);
            if (k < 0) {
                va_end(args);
                free(str);
                free(mini_format);
                return count;
            }
            i += (diff - 1);
            count += k;
            free(mini_format);
            free(str);
        }

        else {
            ++i;
        }
    }

    va_end(args);
    return count;

}
